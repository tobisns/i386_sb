section .text
    [bits 32]
    [extern idt_install]
    [extern idtp]
    [global idt_load]
    [extern main]
    [extern fault_handler]
    [extern isrs_install]
    
    
    call idt_install
    call isrs_install
    call main
    jmp $



    idt_load:
        lidt [idtp]
        ret

    [global isr0]


    isr0:
        cli
        push byte 0
        push byte 0
        jmp isr_common_stub

    


    isr_common_stub:
        pusha
        push ds
        push es
        push fs
        push gs
        mov ax, 0x10
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov eax, esp
        push eax
        mov eax, fault_handler
        call eax
        pop eax
        pop gs
        pop fs
        pop es
        pop ds
        popa
        add esp, 8
        iret