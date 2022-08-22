
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

struct idt_entry idt[256];
struct idt_descriptor idtp;

unsigned short* vid_ptr;


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

extern void isrs_install(){
    idt_set_gate(0,(unsigned)isr0,0x08,0x8e);

    return;
}

unsigned char* exception_messages[] =
{
    'T'
};

extern void fault_handler(struct regs* r){
    if(r->int_no < 32){
        vid_ptr = (unsigned short*)0xb8002; 
        *vid_ptr = 0xa31;//exception_messages[r->int_no];
        for(;;);
    }
}
