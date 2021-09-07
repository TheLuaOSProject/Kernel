print:
    pusha

start:
    mov     al, [bx]

    cmp     al, 0
    je      endprint
    
    mov     ah, 0x0e
    int     0x10

    add     bx, 1
    jmp     start

endprint:
    popa
    ret

newline:
    pusha
    
    mov     ah, 0x0e
    mov     al, 0x0a ; newline char
    int     0x10
    mov     al, 0x0d ; carriage return
    int     0x10
    
    popa
    ret

println:
    call print
    call newline
    ret
;HEX

hexprint:
    pusha
    mov     cx, 0

hex_to_ascii:
    cmp     cx, 4
    je      end_hexprint

    mov     ax, dx
    and     ax, 0x000f ; 0x1234 -> 0x0004 by masking first three to zeros
    add     al, 0x30 ; add 0x30 to N to convert it to ASCII "N"
    cmp     al, 0x39 ; if > 9, add extra 8 to represent 'A' to 'F'

    mov     bx, HEX_OUTPUT + 5 ; base + length
    sub     bx, cx  ; our index variable
    mov     [bx], al ; copy the ASCII char on 'al' to the position pointed by 'bx'
    ror     dx, 4 ; 0x1234 -> 0x4123 -> 0x3412 -> 0x2341 -> 0x1234

    add     cx, 1
    jmp     hex_to_ascii

    add     al, 7

end_hexprint:
    mov     bx, HEX_OUTPUT
    call    print

    popa
    ret

hexprintln:
    call hexprint
    call newline    
    
HEX_OUTPUT: db "0x0000", 0
