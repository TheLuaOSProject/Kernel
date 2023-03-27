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

#include "../../../../common.h"
#include "acpi.h"


NONNULL_BEGIN


struct [[gnu::packed]] MADTEntryHeader {
    byte id, length;
};


struct [[gnu::packed]] MADT {
    struct SDTHeader descriptor;

    dword controller_address, flags;

    /// @warning THIS IS MISLEADING! ENTRIES ARE VARIABLE LENGTH! DO NOT TRY AND INDEX
    struct MADTEntryHeader entries[];
};

//#define MADT_ENTRY_ID_LAPIC (0)
enum MADTEntryID {
    MADTEntryID_LAPIC = 0,
};

struct [[gnu::packed]] MADTEntry_LAPIC {
    struct MADTEntryHeader header;

    byte processor_id, apic_id;
    dword flags;
};

struct MADTEntry_IOAPIC {
    struct MADTEntryHeader header;

    byte id;
    byte reserved;
    dword address, global_system_interrupt_base;
};

struct MADT *nullable madt_init(const struct RSDP *rsdp);


NONNULL_END
