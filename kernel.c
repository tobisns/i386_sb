extern void main(){
    volatile int i = 1/0;
    *(char*)0xb8000 = 'Q';
    return;
}