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
#include "luck/arch/x86_64/interrupts/pit.h"
#include "luck/arch/x86_64/interrupts/idt.h"

#include "luck/arch/x86_64/io/port.h"

void pit_set_frequency(dword frequency)
{
    // The value we send to the PIT is the value to divide it's input clock
    word divisor = 1193180 / frequency;
    port_out_byte(0x43, 0x36);
    port_out_byte(0x40, divisor & 0xFF);
    port_out_byte(0x40, divisor >> 8);
}

void pit_init()
{
    pit_set_frequency(1000);
}
