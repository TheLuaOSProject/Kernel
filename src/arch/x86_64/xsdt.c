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

#include "luck/arch/x86_64/xsdt.h"

#include "luck/arch/x86_64/rsdp.h"

#include "memory.h"
#include "luck/io/log.h"

struct XSDT *get_xsdt(const struct RSDP *desc)
{
    struct XSDT *xsdt = (void *)desc->xsdt_address;

    return sdt_checksum(&xsdt->header) ? xsdt : nullptr;
}

struct SDTHeader *find_sdt(const struct XSDT *table, const char id[static 4], size_t idx)
{
    size_t entryc = (table->header.length - sizeof(struct SDTHeader)) / 8;

    for (size_t i = 0; i < entryc; i++) {
        struct SDTHeader *sdt = (struct SDTHeader *)*((qword *)((byte *)table->data) + i);

        if (idx-- > 0) continue;

        if (memory_compare(sdt->signature, id, 4) != 0) continue;

        return sdt;
    }

    return nullptr;
}


