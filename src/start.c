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

#include "io/console.h"
#include "io/log.h"

#include "cpu/interrupts.h"

void kernel_start()
{
    console.print("\x1b[32mStarted the LuaOS kernel\x1b[0m\n");
    log.write("\nKernel start", 1);

    console.info("Initialising interrupts");
    interrupts.initalise();
    console.success("Done");


    halt();
}
