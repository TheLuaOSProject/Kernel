[BITS 64]

%macro INTERRUPT 1
[EXTERN %1_handler]
[GLOBAL int_%1]
int_%1:
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
    call %1_handler

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

INTERRUPT div_by_zero
INTERRUPT breakpoint
INTERRUPT double_fault
INTERRUPT general_protection
INTERRUPT debug
INTERRUPT invalid_opcode
