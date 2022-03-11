.text
.globl CRASH
CRASH:
    //MOV     X0, 0x0
    //DIV     0x0, X0
    RET

.globl HALT
HALT:
    HLT     #0x1
    RET
