
%macro STACK_START 0

    MOV RDI, RSP

    PUSH R15
    PUSH R14
    PUSH R13
    PUSH R12
    PUSH R11
    PUSH R10
    PUSH R9
    PUSH R8
    PUSH RBP
    PUSH RDI
    PUSH RSI
    PUSH RDX
    PUSH RCX
    PUSH RBX
    PUSH RAX

    CLD

%endmacro

%macro STACK_END 0

    POP RAX
    POP RBX
    POP RCX
    POP RDX
    POP RSI
    POP RDI
    POP RBP
    POP R8
    POP R9
    POP R10
    POP R11
    POP R12
    POP R13
    POP R14
    POP R15

    IRETQ

%endmacro

GLOBAL asm_div_by_zero
EXTERN idiv_by_zero
asm_div_by_zero:
    STACK_START
    call    idiv_by_zero
    STACK_END
    
GLOBAL asm_breakpoint
EXTERN ibreakpoint
asm_breakpoint:
    STACK_START
    call    ibreakpoint
    STACK_END
    
GLOBAL asm_double_fault
EXTERN idouble_fault
asm_double_fault:
    STACK_START
    call    idouble_fault
    STACK_END
    
GLOBAL asm_general_protection
EXTERN igeneral_protection
asm_general_protection:
    STACK_START
    call    igeneral_protection
    STACK_END    
    
GLOBAL asm_keyboard
EXTERN ikeyboard
asm_keyboard:
    STACK_START
    call    ikeyboard
    STACK_END
