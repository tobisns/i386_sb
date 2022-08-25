
struct idt_entry {
    unsigned short base_lo;
    unsigned short sel;
    unsigned char zeroes;
    unsigned char flags;
    unsigned short base_hi;
}__attribute__((packed));

struct idt_descriptor {
    unsigned short limit;
    unsigned int base;
}__attribute__((packed));

struct regs {
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
};

unsigned short* vid_ptr = (short*)0xb8000;

void puts(unsigned char* string, unsigned char color){
    while(*string!='\0'){
        *(vid_ptr++) = (unsigned short)((color << 8)|*(string++));
    }
}



struct idt_entry idt[256];
struct idt_descriptor idtp;

extern void idt_load();

void* memset(void* dest, char val, long count){
    char* temp = (char*)dest;
    for(; count != 0; count--) *temp++ = val;
    return dest;
}

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags){
    idt[num].base_lo = (base & 0xffff);
    idt[num].base_hi = (base >> 16) & 0xffff;
    idt[num].sel = sel;
    idt[num].zeroes = 0;
    idt[num].flags = flags;

}

extern void idt_install(){
    idtp.limit = (sizeof(struct idt_entry)*256) - 1;
    idtp.base = &idt;

    memset(&idt,0,sizeof(struct idt_entry)*256);

    idt_load();
    *(char*)0xb8002 = 'X';
    return;
}

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void isrs_install(){
    idt_set_gate(0,(unsigned)isr0,0x08,0x8e);
    idt_set_gate(1,(unsigned)isr1,0x08,0x8e);
    idt_set_gate(2,(unsigned)isr2,0x08,0x8e);
    idt_set_gate(3,(unsigned)isr3,0x08,0x8e);
    idt_set_gate(4,(unsigned)isr4,0x08,0x8e);
    idt_set_gate(5,(unsigned)isr5,0x08,0x8e);
    idt_set_gate(6,(unsigned)isr6,0x08,0x8e);
    idt_set_gate(7,(unsigned)isr7,0x08,0x8e);
    idt_set_gate(8,(unsigned)isr8,0x08,0x8e);
    idt_set_gate(9,(unsigned)isr9,0x08,0x8e);
    idt_set_gate(10,(unsigned)isr10,0x08,0x8e);
    idt_set_gate(11,(unsigned)isr11,0x08,0x8e);
    idt_set_gate(12,(unsigned)isr12,0x08,0x8e);
    idt_set_gate(13,(unsigned)isr13,0x08,0x8e);
    idt_set_gate(14,(unsigned)isr14,0x08,0x8e);
    idt_set_gate(15,(unsigned)isr15,0x08,0x8e);
    idt_set_gate(16,(unsigned)isr16,0x08,0x8e);
    idt_set_gate(17,(unsigned)isr17,0x08,0x8e);
    idt_set_gate(18,(unsigned)isr18,0x08,0x8e);
    idt_set_gate(19,(unsigned)isr19,0x08,0x8e);
    idt_set_gate(20,(unsigned)isr20,0x08,0x8e);
    idt_set_gate(21,(unsigned)isr21,0x08,0x8e);
    idt_set_gate(22,(unsigned)isr22,0x08,0x8e);
    idt_set_gate(23,(unsigned)isr23,0x08,0x8e);
    idt_set_gate(24,(unsigned)isr24,0x08,0x8e);
    idt_set_gate(25,(unsigned)isr25,0x08,0x8e);
    idt_set_gate(26,(unsigned)isr26,0x08,0x8e);
    idt_set_gate(27,(unsigned)isr27,0x08,0x8e);
    idt_set_gate(28,(unsigned)isr28,0x08,0x8e);
    idt_set_gate(29,(unsigned)isr29,0x08,0x8e);
    idt_set_gate(30,(unsigned)isr30,0x08,0x8e);
    idt_set_gate(31,(unsigned)isr31,0x08,0x8e);

    return;
}

unsigned char* exception_messages[] =
{
    "Error, Division by Zero! :D",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint Exception",
    "Into Detected Overflow Exception",
    "Out of Bound",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrut",
    "Coprocessor Fault",
    "Aligment Check Exception",
    "Machine Check Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

extern void fault_handler(struct regs* r){
    if(r->int_no < 32){
        puts(exception_messages[r->int_no],0x1a);//exception_messages[r->int_no];
        for(;;);
    }
}
