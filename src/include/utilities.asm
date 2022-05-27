///
///@file utilities.asm
///@author Amrit Bhogal
///@version 1.0.0 - Amrit Bhogal on 2022-05-26
///

//noreturn void HALT(void);
.global HALT
.type   HALT, @function
HALT:
    B   HALT

//void  MEMORY_COPY(void *dst, void *src, uint64 nmemb);
.global MEMORY_COPY
.type   MEMORY_COPY, @function
MEMORY_COPY:
    CBZ     X2,  1f         //Compares X2 with 0, and if true, jumps to .END
    LDRB    W10, [X0], #1   //Loads the byte from src into register W10, and increments src
    STRB    W10, [X1], #1   //Stores the byte from W10 into dst, and increments dst 
    SUBS    X2, X2, #1      //Decrement the counter
    B       MEMORY_COPY     //Redo!
    1:
    RET
    
//void  MEMORY_SET(void *dst, uint64 val, uint64 nmemb);
.global MEMORY_SET
.type   MEMORY_SET, @function
MEMORY_SET:
    CBZ     X2, 1f
    STRB    W1, [X0], #1
    SUBS    X2, X2, #1
    1:
    RET
