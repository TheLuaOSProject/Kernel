GLOBAL CRASH
CRASH:
    UD2         ;Funny instruction
    RET         ;lol

GLOBAL DIV_BY_ZERO
DIV_BY_ZERO:
    MOV     EAX, 4
    MOV     EBX, 0
    DIV     EBX
    RET
    
GLOBAL DEBUG_INTERRUPT
DEBUG_INTERRUPT:
    INT     0x72   
    RET

GLOBAL BREAKPOINT
BREAKPOINT:
    INT     0x3
    RET

GLOBAL HALT
HALT:
    HLT
    RET

