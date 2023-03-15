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

#define LAPIC_IMPL
#include "luck/arch/x86_64/interrupts/lapic.h"

#include "stdint.h"

#include "luck/arch/x86_64/cpu.h"
#include "luck/arch/x86_64/interrupts/idt.h"
#include "luck/arch/x86_64/msr.h"
#include "luck/io/log.h"

#define VECTOR_ID (0xEF)
#define TIMER_DIV (0x10)

static volatile dword *lapic_base = 0;
extern void int_lapic_timer(void *);

dword lapic_read(enum LAPICRegister reg)
{ return lapic_base[reg / 4]; }

void lapic_write(enum LAPICRegister reg, dword value)
{ lapic_base[reg / 4] = value; }

static volatile qword counter;
[[gnu::used]]
void lapic_timer_handler(CPUContext *ctx)
{
    counter++;
    lapic_write(LAPICRegister_END_OF_INTERRUPT, 0x0);

    if (counter % 100 == 0) {
        counter = 0;
        debug("LAPIC Timer!");
    }
}

void lapic_init(void)
{
    qword apic_base_msr = read_msr(APIC_BASE_MSR);
    apic_base_msr |= (1 << 11);
    write_msr(APIC_BASE_MSR, apic_base_msr);

    lapic_base = (volatile dword *)((apic_base_msr & 0xFFFFF000) + 0xFFFF800000000000);

    // Set task priority to the lowest (allow all interrupts)
    lapic_write(LAPICRegister_PRIORITY, 0);

    idt_register_int(VECTOR_ID, &int_lapic_timer);
    dword timer = lapic_read(LAPICRegister_LVT_TIMER);
    timer &= ~(1 << 16); //clear mask to enable interrupt
    timer |= VECTOR_ID;
    lapic_write(LAPICRegister_LVT_TIMER, timer);

    //setup for div config
    dword divcfg = lapic_read(LAPICRegister_DIVIDE_CONFIG);
    divcfg &= 0b1011; //clear these bits because intel
    divcfg |= ((TIMER_DIV - 1) & 0b1011) << 1;
    lapic_write(LAPICRegister_DIVIDE_CONFIG, divcfg);

    //Set the init count to smth big
    lapic_write(LAPICRegister_INITAL_COUNT, 1000000);
}
