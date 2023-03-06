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

%macro INTERRUPT 1
[EXTERN %1_handler]
[GLOBAL int_%1]
int_%1:

    ; Call the interrupt handler
    CLD
    CALL %1_handler

    IRETQ

%endmacro


INTERRUPT div_by_zero
INTERRUPT breakpoint
INTERRUPT double_fault
INTERRUPT general_protection
INTERRUPT debug
INTERRUPT invalid_opcode
