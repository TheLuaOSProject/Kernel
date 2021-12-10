
[BITS 64]

[GLOBAL LOAD_IDT]
LOAD_IDT:
    LIDT [RDI]
    STI
    RET


[GLOBAL ASM_DIV_BY_ZERO]
[EXTERN div_by_zero_i]
ASM_DIV_BY_ZERO:
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
    
    
    call div_by_zero_i
    
    
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


[GLOBAL ASM_BREAKPOINT]
[EXTERN breakpoint_i]
ASM_BREAKPOINT:

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
    
    
    call breakpoint_i
    
    
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


[GLOBAL ASM_DOUBLE_FAULT]
[EXTERN double_fault_i]
ASM_DOUBLE_FAULT:

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
    
    
    call double_fault_i
    
    
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


[GLOBAL ASM_GENERAL_PROTECTION]
[EXTERN general_protection_i]
ASM_GENERAL_PROTECTION:
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
    
    
    call general_protection_i
    
    
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


[GLOBAL ASM_DEBUG]
[EXTERN debug_i]
ASM_DEBUG:

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
    
    
    call debug_i
    
    
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


[GLOBAL ASM_INVALID_OPCODE]
[EXTERN invalid_opcode_i]
ASM_INVALID_OPCODE:

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
    
    
    call invalid_opcode_i
    
    
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

