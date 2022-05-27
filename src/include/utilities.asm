///
///@file utilities.asm
///@author Amrit Bhogal
///@version 1.0.0 - Amrit Bhogal on 2022-05-26
///

.global HALT
.type   HALT, @function
HALT:
    B HALT
    RET
