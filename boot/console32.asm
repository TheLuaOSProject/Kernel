[bits 32]

VIDEO_MEMORY    equ 0xb8000
DEFAULT_COLOUR  equ 0xA

print32:
    pusha
    mov         edx, VIDEO_MEMORY

putchar32:
    mov         al, [ebx]
    mov         ah, DEFAULT_COLOUR

    cmp         al, 0
    je          end_print32

    mov         [edx], ax
    add         ebx, 1
    add         edx, 2

    jmp         putchar32

end_print32:
    popa
    ret
