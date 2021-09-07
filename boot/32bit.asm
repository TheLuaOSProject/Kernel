[bits 16]
protmode_switch:
    cli
    lgdt        [gdt_descriptor]
    mov         eax, cr0
    or          eax, 0x1
    mov         cr0, eax

    jmp         CODE_SEG:protmode_init


[bits 32]
protmode_init:
    mov         ebx, INIT_32
    call        print32
    
    mov         ax, DATA_SEG
    
    mov         ds, ax  
    mov         ss, ax
    mov         es, ax
    mov         fs, ax
    mov         gs, ax

    mov         ebp, 0x90000
    mov         esp, ebp

    ;in boot.asm
    call        protmode_start

INIT_32         db "INIT 32 BIT MODE", 0
