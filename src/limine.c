/**
 * Copyright (C) 2023 pitust
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

#include "kern/io/log.h"
#include <limine.h>

static volatile struct limine_hhdm_request hhdm_request = {LIMINE_HHDM_REQUEST, 0, nullptr};
static volatile struct limine_kernel_address_request kaddr = {LIMINE_KERNEL_ADDRESS_REQUEST, 0, nullptr};

uint64_t _limine__virt_to_phys(uint64_t virt) {
	if (virt >= kaddr.response->virtual_base) return virt - kaddr.response->virtual_base + kaddr.response->physical_base;
	if (virt >= 0xffff800000000000) return virt - hhdm_request.response->offset;
	panic("invalid call to virt_to_phys({:#x}) [invalid va]", virt);
}
uint64_t _limine__phys_to_virt(uint64_t phys) {
	if (phys >= 0xffff800000000000)  panic("invalid call to phys_to_virt()");
	return phys + hhdm_request.response->offset;
}
