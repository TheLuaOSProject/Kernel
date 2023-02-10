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

#include "luck/arch/x86_64/rsdp.h"
#include "luck/io/log.h"

#include <limine.h>
#include "string.h"

static volatile struct limine_rsdp_request request = {
    .id = LIMINE_RSDP_REQUEST,
    .revision = 0
};


struct RSDP *get_rsdp()
{
    struct limine_rsdp_response *resp = request.response;

    //Possible UB?
    if (resp == nullptr || resp->address == nullptr)
        return nullptr;

    struct RSDP *rsdp = resp->address;

    if (rsdp->revision < 2) {
        error("  XSDT not supported on this machine!");
        //Techinically should use RSDT here but im lazy lol
        return nullptr;
    }

    return rsdp;
}


