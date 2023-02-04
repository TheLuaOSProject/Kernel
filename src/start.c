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

#import <limine.h>

#include "kern/io/log.h"
#include "kern/arch/x86/gdt.h"
#include "kern/arch/x86/interrupts.h"

void kernel_start()
{
    gdt_init();
    idt_init();

    info("started the luaOS kernel!");
    info("2 + 2 = {:~^15}", 4);

    asm("ud2");
    halt();
}
