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
    
GLOBAL ADD_ASM
ADD_ASM:
    MOV     EAX, 0
    ADD     EAX, RDI
    ADD     EAX, RSI
    PUSH    EAX
    RET
      
   