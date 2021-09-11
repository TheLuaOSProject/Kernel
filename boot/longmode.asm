%define PAGING_FLAGS (1 << 0) | (1 << 1)

%define CODE_SEGMENT 0x0008
%define DATA_SEGMENT 0x0010

IDT:
    .length       dw 0
    .base         dd 0    

lm_switch:
    push    di
    mov     ecx, 0x1000
    xor     eax, eax
    cld
    rep     stosd
    pop     di
    
    lea     eax, [es:di + 0x1000]
    or      eax, PAGING_FLAGS
    mov     [es:di], eax
    
    lea     eax, [es:di + 0x2000]
    or      eax, PAGING_FLAGS
    mov     [es:di + 0x1000], eax
    
    lea     eax, [es:di + 0x3000]
    or      eax, PAGING_FLAGS
    mov     [es:di + 0x2000], eax
    
    push    di
    lea     di, [di + 0x3000]
    mov     eax, PAGING_FLAGS
    
lm_pagetbl:
    mov     [es:di], eax
    add     eax, 0x1000
    add     di, 8
    cmp     eax, 0x200000
    jb      lm_pagetbl
    
    pop     di
    
    mov     al, 0xFF
    out     0xA1, al
    out     0x21, al
    
    nop
    nop
    
    lidt   [IDT]
    
    ; LONG MODE ENTRY
    ; ---------------
    
    mov     eax, 10100000b
    mov     cr4, eax
    
    mov     edx, edi
    mov     cr3, edx
    
    mov     edx, 0xC0000080
    rdmsr
    
    or      eax, 0x00000100
    wrmsr
    
    mov     ebx, cr0
    or      ebx, 0x80000001
    mov     cr0, ebx
    
    lgdt    [GDT.descriptor]
    
    jmp     CODE_SEGMENT:lm_start
    
GDT:
    .null: 
        dq  0x0000000000000000
   
    .code:
        dq  0x00209A0000000000
        dq  0x0000920000000000
    
    ALIGN   4
        dw  0
    
    .descriptor:
        dw  $ - GDT - 1
        dd  GDT
 
   
[bits 64]
lm_start:
    mov     DATA_SEGMENT
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    mov     ss, ax
    
    mov     edi, 0xB8000
    mov     rcx, 500
    mov     rax, 0x1F201F201F201F20
    rep     stosq                                   

    jmp     bootloader_start 