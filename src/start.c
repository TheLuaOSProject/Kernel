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

#include <limine/limine.h>

#include "common.h"
#include "lj-libc/limits.h"
#include "luck/io/log.h"

#include "luck/arch/x86_64/acpi/madt.h"
#include "luck/arch/x86_64/acpi/acpi.h"
#include "luck/io/console.h"
#include "luck/io/framebuffer.h"
#include "luck/arch/x86_64/gdt.h"
#include "luck/arch/x86_64/interrupts/idt.h"
#include "luck/arch/x86_64/interrupts/lapic.h"
#include "luck/arch/x86_64/io/ps2.h"
#include "luck/processes/scheduler.h"
#include "luck/memory/manager.h"
#include "luck/memory/magazines.h"

#undef stdin
#undef stdout
#undef stderr

NONNULL_BEGIN

static const char *nullable extension(size_t buflen, const char buf[buflen])
{
    //Find the last dot
    size_t i = buflen;
    while (i > 0 && buf[i] != '.') i--;

    if (i == 0) return nullptr;
    return &buf[i + 1];
}

static void stdout_write(const char *str, int siz)
{
    while (siz) {
        console_write_char(*str++);
        siz--;
    }
}

static void ps2_gets(char *buf)
{
    char *start = buf;
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

static volatile struct limine_module_request module_req [[gnu::used]] = {
    LIMINE_MODULE_REQUEST, 0, nullptr
};

static const volatile struct limine_framebuffer_request fb_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST
};


[[gnu::used]] noreturn void kernel_start()
{
    asm (
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
    asm("MOVQ %%CR3, %0" : "=r"(cr3));
    for (qword i = 0; i < 256; i++)
        *virt(cr3 + i * 8, qword) = 0;

    asm("MOVQ %0, %%CR3" :: "r"(cr3) : "memory");


    success("\nStarted LuaOS");
    info("{} + {} = {}", 2, 2, 2 + 2);
    info("Hello, {}", "World!");

    info("Initialising GDT");
    gdt_init();
    success("Done");

    info("Initialising IDT");
    idt_init();
    success("Done");
    asm("STI");

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

    if (fb_request.response == nullptr || fb_request.response->framebuffer_count == 0)
        panic("No framebuffer found!");

    auto fb = fb_request.response->framebuffers[0];

    terminal_init(fb);
    framebuffer_init(fb);

    info("Initialising APIC");
    auto rsdp = assert_nonnull(rsdp_init())({ panic("No RSDP found"); });
    auto madt = assert_nonnull(madt_init(rsdp))({ panic("No MADT found"); });

    size_t core_c = 0;

    for (struct MADTEntryHeader *entry = (struct MADTEntryHeader *)madt->entries;
         (uintptr_t)entry < (uintptr_t)(((uintptr_t)madt->entries) + madt->descriptor.length - sizeof(struct MADT));
         entry = (struct MADTEntryHeader *)((byte *)entry + (entry)->length)) {

        debug("  Found entry with ID {}", entry->id);
        switch (entry->id) {
            case MADTEntryID_LAPIC: {
                struct MADTEntry_LAPIC *lapic = (struct MADTEntry_LAPIC *) entry;
                success("  Found LAPIC at core {} (address: {})", core_c++, lapic);
                debug("    Processor ID: {}", lapic->processor_id);
                debug("    APIC ID: {}", lapic->apic_id);
                debug("    Flags: {}", lapic->flags);
                break;
            }
        }
    }
    success("Done");

    info("Initalising LAPIC");
    lapic_init();
    info("LAPIC base: {}", lapic_base);
    success("Done");
    FILE *stdout = _get_pcb()->stdout = kalloc(sizeof(FILE));
    stdout->write = stdout_write;

    if (module_req.response == nullptr) panic("no modules available!");
    if (module_req.response->module_count == 0) panic("more than one module available!");

    info("Initialising scheduler");
    scheduler_init();
    success("Done");

    Thread *nullable active_threads[module_req.response->module_count];
    for (size_t i = 0; i < module_req.response->module_count; i++) {
        struct limine_file *m = module_req.response->modules[i];
        auto ext = assert_nonnull(extension(string_length(m->cmdline), m->cmdline))({ continue; });
        if (string_compare(string_length(ext), ext, 3, "lua") != 0) continue;

        active_threads[i] = spawn_thread(m->address, m->size, m->cmdline);
    }

    success("Initalisation complete");
    halt();
}

NONNULL_END
