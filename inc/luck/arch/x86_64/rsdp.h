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

#include "sdt.h"

NONNULL_BEGIN

struct RSDP {
    //1.0
    char signature[8];
    byte checksum;
    char oem_id[6];
    byte revision;
    dword rsdt_address;

    //2.0
    dword length;
    qword xsdt_address;
    byte extended_checksum, reserved[3];
} attribute(packed);

struct RSDP *nullable rsdp_init();

NONNULL_END
