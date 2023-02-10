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

#include "luck/memory/manager.h"
#include "luck/memory/magazines.h"
#include "luck/io/log.h"
#include "luck/arch/x86_64/gdt.h"
#include "luck/arch/x86_64/interrupts.h"
#include "luck/arch/x86_64/rsdp.h"

void kernel_start()
{
    warning("Stage 1: Initalisation");
    info("Initialising GDT");
    gdt_init();
    success("Done");

    info("Initialising IDT");
    idt_init();
    success("Done");

    info("Initialising memory");
    info("  Magazines...");
    magazine_init();
    success("  Done");

    info("  Kernel memory allocator...");
    kalloc_init();
    success("  Done");
    success("Done");

    info("Initialising PIC");
    pic_init(0x20, 0x28);
    info("  Finding RSDP");
    struct RSDP *rsdp = get_rsdp();
    if (rsdp == nullptr)
        error("  no RSDP found!");
    else {
        info("  RSDP found at {:#x}", (void *) rsdp);
        info("  RSDP revision: {}", rsdp->revision);
        info("  RSDP length: {}", rsdp->length);
        info("  RSDP xsdt_address: {:#x}", rsdp->xsdt_address);
        info("  RSDP rsdt_address: {:#x}", rsdp->rsdt_address);
        success("  Done");
    }
    success("Done");

    success("Initalisation complete");
    halt();
}
