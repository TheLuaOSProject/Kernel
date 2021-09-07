[org 0x7c00]

KERNEL_OFFSET       equ 0x1000

mov                 bx, BOOT
call                println

mov                 [BOOTDRIVE], dl

mov                 bp, 0x9000
mov                 sp, bp

call                load_kernel
call                protmode_switch

jmp                 $

%include "boot/console16.asm"
%include "boot/32bit.asm"
%include "boot/gdt.asm"
%include "boot/console32.asm"
%include "boot/disk.asm"

[bits 16]
load_kernel:
    mov             bx, KERNEL_LOAD
    call            println

    mov             bx, KERNEL_OFFSET
    mov             dh, 16
    mov             dl, [BOOTDRIVE]

    call            load_disk

    mov             bx, DISK_LOADED
    call            println

    ret

[bits 32]
protmode_start:
    mov             ebx, PROTMODE_LOADED
    call            print32
    call            KERNEL_OFFSET
    jmp             $


BOOTDRIVE           db 0

BOOT                db "BEGIN", 0
KERNEL_LOAD         db "LOADING KERNEL", 0
DISK_LOADED         db "LOADED DISK AND KERNEL", 0
PROTMODE_LOADED     db "LOADED 32 BIT (PROTECTED) MODE", 0


times 510 - ($-$$)  db 0
dw                  0xaa55