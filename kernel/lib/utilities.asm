GLOBAL CRASH
CRASH:
    UD2         ;Funny instruction

GLOBAL DIV_BY_ZERO
DIV_BY_ZERO:
    MOV     EAX, 4
    MOV     EBX, 0
    DIV     EBX
   