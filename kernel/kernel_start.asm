[bits 32]
[extern kernel_start]

mov             ebx, KERNEL_BEGIN
call            print32

call            kernel_start
jmp             $


%include "boot/console32.asm"

KERNEL_BEGIN     db "KERNEL START", 0   