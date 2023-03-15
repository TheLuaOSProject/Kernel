; 
; Copyright (C) 2023 Amrit Bhogal
;
; This file is part of LuaOS.
;
; LuaOS is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
;
; LuaOS is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with LuaOS.  If not, see <http://www.gnu.org/licenses/>.
;


[BITS 64]
[SECTION .text]
%macro INTERRUPT 1
[EXTERN %1_handler]
[GLOBAL int_%1]
int_%1:
    ;Already pushed:
    ;PUSH RIP
    ;PUSH CS
    ;PUSH RFLAGS
    ;PUSH RSP
    ;PUSH SS

    PUSH    R15
    PUSH    R14
    PUSH    R13
    PUSH    R12
    PUSH    R11
    PUSH    R10
    PUSH    R9
    PUSH    R8
    PUSH    RBP
    PUSH    RDI
    PUSH    RSI
    PUSH    RDX
    PUSH    RCX
    PUSH    RBX
    PUSH    RAX

    MOV     RDI, RSP
    CALL    %1_handler

    POP     RAX
    POP     RBX
    POP     RCX
    POP     RDX
    POP     RSI
    POP     RDI
    POP     RBP
    POP     R8
    POP     R9
    POP     R10
    POP     R11
    POP     R12
    POP     R13
    POP     R14
    POP     R15
    ADD     RSP, 8

    IRETQ
%endmacro

INTERRUPT div_by_zero
INTERRUPT breakpoint
INTERRUPT double_fault
INTERRUPT general_protection
INTERRUPT debug
INTERRUPT invalid_opcode
INTERRUPT lapic_timer
