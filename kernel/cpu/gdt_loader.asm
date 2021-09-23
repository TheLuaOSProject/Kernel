[bits 64]
load_gdt:
    lgdt                [rdi]       ; Loads the GDT from the RDI register, which is where the GDT will be located once called from the Kernel
    mov                 ax, 0x10    ; Selector for the kernel data segment 
    mov                 ds, ax      ; Load the kernel data segment into all of the data segment registers
    mov                 es, ax
    mov                 fs, ax
    mov                 gs, ax
    mov                 ss, ax
    pop                 rdi
    mov                 rax, 0x08   ; Kernel code segment selector 
    push                rax
    push                rdi
    retfq

GLOBAL  load_gdt    
    