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

#include "luck/arch/x86_64/pic.h"

#include "luck/io/port.h"

void pic_init(int master_offset, int slave_offset)
{
    byte master_mask = port_in_byte(MASTER_PIC), slave_mask = port_in_byte(SLAVE_PIC);

    // Init init sequence
    port_out_byte(MASTER_PIC, ICW1_INIT | ICW1_ICW4);
    port_out_byte(SLAVE_PIC, ICW1_INIT | ICW1_ICW4);

    // Set offsets
    port_out_byte(MASTER_PIC_DATA, master_offset);
    port_out_byte(SLAVE_PIC_DATA, slave_offset);

    // Tell master about slave
    port_out_byte(MASTER_PIC_DATA, 0b00000100/* IRQ2 */);
    port_out_byte(SLAVE_PIC_DATA, 0b00000010/* Cascade identity */);

    // Set mode
    port_out_byte(MASTER_PIC_DATA, ICW4_8086);
    port_out_byte(SLAVE_PIC_DATA, ICW4_8086);

    // Restore masks
    port_out_byte(MASTER_PIC_DATA, master_mask);
    port_out_byte(SLAVE_PIC_DATA, slave_mask);
}

void pic_send_eoi(byte irq)
{
    if (irq >= 8) port_out_byte(SLAVE_PIC_CMD, PIC_END_OF_INT);
    port_out_byte(MASTER_PIC_CMD, PIC_END_OF_INT);
}
