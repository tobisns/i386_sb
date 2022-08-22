#!/bin/sh

export PATH=$PATH:/usr/local/i386elfgcc/bin

nasm "boot.asm" -f bin -o "Binaries/boot.bin"
nasm "kernel_entry.asm" -f elf -o "Binaries/kernel_entry.o"
i386-elf-gcc -ffreestanding -m32 -g -c -Wno-div-by-zero "kernel.c" -o "Binaries/kernel.o"
i386-elf-gcc -ffreestanding -m32 -g -c -Wno-div-by-zero "idt.c" -o "Binaries/idt.o"
nasm "zeroes.asm" -f bin -o "Binaries/zeroes.bin"

i386-elf-ld -o "Binaries/full_kernel.bin" -Ttext 0x1000 "Binaries/kernel_entry.o" "Binaries/idt.o" "Binaries/kernel.o" --oformat binary

cat "Binaries/boot.bin" "Binaries/full_kernel.bin" "Binaries/zeroes.bin" > "Binaries/OS.bin"

#cleaning obj
rm  "Binaries/kernel_entry.o" "Binaries/kernel.o"  "Binaries/idt.o"

qemu-system-x86_64 -drive format=raw,file="Binaries/OS.bin",index=0,if=floppy,file.locking=off, -m 128M