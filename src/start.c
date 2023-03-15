/**
 * Copyright (C) 2023 Amrit Bhogal
 *
 * This file is part of LuaOS.
 *
 * LuaOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LuaOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LuaOS.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <limine.h>

#include "lj-libc/limits.h"
#include "luck/io/log.h"

#include "luck/acpi/madt.h"
#include "luck/acpi/acpi.h"
#include "luck/io/console.h"
#include "luck/arch/x86_64/gdt.h"
#include "luck/arch/x86_64/idt.h"
#include "luck/io/ps2.h"
#include "luck/memory/manager.h"
#include "luck/memory/magazines.h"

#include "../luajit/src/lua.h"

#undef stdin
#undef stdout
#undef stderr

///
/// @category LuaJIT Support
/// LuaJIT allocator (defined in src/lib/libsupport.c)
///
void *ljsup_alloc(void *ud, void *ptr, size_t osize, size_t nsize);

///
/// @category LuaJIT Support
///
///
int luaL_loadbuffer(lua_State *L, const char *s, size_t len, const char *name);

void luaJIT_version_2_1_0_beta3(void);

void LJDBG(const char* msg) {success("lj: {}", msg);}

#define _lua_openmodule(mname, module) \
    lua_pushcfunction(L, luaopen_##module); \
    lua_pushstring(L, mname); \
    lua_call(L, 1, 0);
#define lua_openmodule(module) _lua_openmodule(#module, module)

LUALIB_API int luaopen_base(lua_State *L);
LUALIB_API int luaopen_math(lua_State *L);
LUALIB_API int luaopen_string(lua_State *L);
LUALIB_API int luaopen_table(lua_State *L);
LUALIB_API int luaopen_debug(lua_State *L);
LUALIB_API int luaopen_bit(lua_State *L);

void stdout_write(const char *str, int siz) {
    while (siz) {
        console_write_char(*str++);
        siz--;
    }
}
static void ps2_gets(char* buf) {
    char* start = buf;
    while (true) {
        char c = ps2_getc();
        if (c == '\n') {
            stdout_write("\n", 1);
            *buf = 0;
            return;
        }
        if (c == '\b') {
            if (buf == start) continue;
            buf--;
            stdout_write("\b \b", 3);
            continue;
        }
        *buf++ = c;
        stdout_write(&c, 1);
    }
}

[[gnu::used]] noreturn void kernel_start()
{
    asm(
        ".intel_syntax noprefix\n"
        "mov rax, cr0\n"
        "and ax, 0xFFFB\n"
        "or ax, 0x2\n"
        "mov cr0, rax\n"
        "mov rax, cr4\n"
        "or ax, 3 << 9\n"
        "mov cr4, rax\n"
        ".att_syntax\n"
    );

    qword cr3;
    asm volatile("MOVQ %%CR3, %0" : "=r"(cr3));
    for (qword i = 0;i < 256;i++) {
        *virt(cr3 + i * 8, qword) = 0;
    }
    asm volatile("MOVQ %0, %%CR3" :: "r"(cr3) : "memory");


    success("\nStarted LuaOS");
    info("{} + {} = {}", 2, 2, 2 + 2);
    info("Hello, {}", "World!");

    info("Initialising GDT");
    gdt_init();
    success("Done");

    info("Initialising IDT");
    idt_init();
    success("Done");

    info("Initialising memory");
    {
        info("  Magazines...");
        magazine_init();
        success("  Done");

        info("  Kernel memory allocator...");
        kalloc_init();
        success("  Done");
    }
    success("Done");

    initalise_terminal();

    info("Initialising APIC");
    struct RSDP *rsdp = rsdp_init();
    if (rsdp == nullptr)
        panic("Could not find RSDP");

    struct MADT *madt = madt_init(rsdp);
    if (madt == nullptr) panic("Could not find MADT");

    size_t core_c = 0;

    for (struct MADTEntryHeader *entry = (struct MADTEntryHeader *)madt->entries;
         (uintptr_t)entry < (uintptr_t)(((uintptr_t)madt->entries) + madt->descriptor.length - sizeof(struct MADT));
         entry = (struct MADTEntryHeader *)((byte *)entry + (entry)->length)) {

        debug("  Found entry with ID {}", entry->id);
        switch (entry->id) {
            case MADT_ENTRY_ID_LAPIC: {
                struct MADTEntry_LAPIC *lapic = (struct MADTEntry_LAPIC *) entry;
                success("  Found LAPIC at core {} (address: {})", core_c++, //lol
                        (void *) lapic);
                debug("    Processor ID: {}", lapic->processor_id);
                debug("    APIC ID: {}", lapic->apic_id);
                debug("    Flags: {}", lapic->flags);
                break;
            }
        }
    }
    success("Done");

    int status;
    lua_State *L;


    L = lua_newstate(ljsup_alloc, nullptr); // open Lua
    if (!L) {
        panic("cant open lua");
    }
    
    _lua_openmodule("", base);
    lua_openmodule(table);
    lua_openmodule(string);
    lua_openmodule(math);
    lua_openmodule(debug);
    lua_openmodule(bit);
    FILE* stdout = _get_pcb()->stdout = kalloc(sizeof(FILE));
    stdout->write = stdout_write;

    const char *in = "print('what is the best language? it\\'s LUA, of course!')";
    int v = luaL_loadbuffer(L, in, string_length(in), "entry");
    if (v != 0) {
        panic("fail {}", lua_tostring(L, -1));
    }
    lua_call(L, 0, 0);

    while (true) {
        char buf[4096];
        stdout_write("> ", 2);
        ps2_gets(buf);

        int v = luaL_loadbuffer(L, buf, string_length(buf), "stdin");
        if (v != 0) {
            error("fail {}", lua_tostring(L, -1));
        } else {
            lua_call(L, 0, 0);
        }
    }

    success("Initalisation complete");
    asm volatile("UD2");
    halt();
}
