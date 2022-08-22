
[org 0x7c00]

KERNEL_LOCATION equ 0x1000


mov [DISKBOOT], dl

xor ax, ax
mov es, ax
mov ds, ax
mov bp, 0x8000
mov sp, bp

mov bx, KERNEL_LOCATION
mov dh, 4

mov ah, 0x02
mov al, dh
mov ch, 0x00
mov dh, 0x00
mov cl, 0x02
mov dl, [DISKBOOT]
int 0x13
;jc cflag

mov ah, 0x0
mov al, 0x3
int 0x10        ;text mode

CODE_SEG equ code_descriptor - GDTstart
DATA_SEG equ data_descriptor - GDTstart

cli
lgdt [GDTdescriptor]
mov eax, cr0
or eax, 1
mov cr0, eax
jmp CODE_SEG:start_protected_mode

jmp $

DISKBOOT: db 0


cflag:
    mov ah, 0x0e
    mov al, 'X'
    int 0x10
    jmp $

GDTstart:
    null_descriptor:
        dd 0x0
        dd 0x0
    code_descriptor:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10011010
        db 0b11001111
        db 0x0
    data_descriptor:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10010010
        db 0b11001111
        db 0x0
GDTend:

GDTdescriptor:
    dw GDTend - GDTstart - 1
    dd GDTstart


[bits 32]
start_protected_mode:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    jmp KERNEL_LOCATION


times 510-($-$$) db 0
dw 0xaa55