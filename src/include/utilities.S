.text
.globl CRASH
CRASH:
    MOV     R0, #0x0
    DIV     R0, #0x1
    RET

.globl HALT
HALT:
    HLT
    RET
