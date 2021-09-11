[org 0x7c00]

luaos_boot:
    mov                 [BOOTDRIVE], dl
    call                load_kernel
    
    xor                 ax, ax
    mov                 ss, ax
    
    mov                 sp, luaos_boot
    
    mov                 ds, ax
    mov                 es, ax
    mov                 fs, ax
    mov                 gs, ax
    cld
    
    mov                 edi, 0x9000  

    jmp                 lm_switch             
    jmp                 $

%include "boot/longmode.asm"  
%include "boot/disk.asm"

[bits 16]
load_kernel:
    mov             bx, 0x1000
    mov             dh, 16
    mov             dl, [BOOTDRIVE]

    call            load_disk
    ret
    
[bits 64]    
bootloader_start:
    call            0x1000 ;Kernel Location
    jmp             $

BOOTDRIVE           db 0

times 510 - ($-$$)  db 0
dw                  0xaa55