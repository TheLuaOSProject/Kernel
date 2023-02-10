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

struct SDTHeader {
    char signature[4];
    dword length;
    byte revision, checksum;
    char oem_id[6], oem_table_id[8];
    dword oem_revision, creator_id, creator_revision;
};

inline bool sdt_checksum(struct SDTHeader *header)
{
    byte sum = 0;
    for (size_t i = 0; i < header->length; i++) {
        sum += ((byte *)header)[i];
    }
    return sum == 0;
}

NONNULL_END
