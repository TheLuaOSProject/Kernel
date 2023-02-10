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

#pragma once

#include "common.h"

NONNULL_BEGIN

#define MASTER_PIC      (0x20)
#define SLAVE_PIC       (0xA0)
#define MASTER_PIC_CMD  (MASTER_PIC)
#define MASTER_PIC_DATA (MASTER_PIC + 1)
#define SLAVE_PIC_CMD   (SLAVE_PIC)
#define SLAVE_PIC_DATA  (SLAVE_PIC + 1)
#define PIC_END_OF_INT  (0x20)

#define ICW1_ICW4       (0x01)
#define ICW1_SINGLE     (0x02)
#define ICW1_INTERVAL4  (0x04)
#define ICW1_LEVEL      (0x08)
#define ICW1_INIT       (0x10)
#define ICW4_8086       (0x01)
#define ICW4_AUTO       (0x02)
#define ICW4_BUF_SLAVE  (0x08)
#define ICW4_BUF_MASTER (0x0C)
#define ICW4_SFNM       (0x10)

void pic_init(int master_offset, int slave_offset);
void pic_send_eoi(byte irq);

NONNULL_END
