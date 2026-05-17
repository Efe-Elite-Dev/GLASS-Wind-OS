#!/bin/bash
echo "=== Wind OS Derleme Motoru Başlatıldı ==="

# 1. Assembly Dosyalarını Derle
nasm -f elf32 boot.asm -o boot.o

# 2. C Dosyalarını Derle (setup.c dahil edildi)
gcc -m32 -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c setup.c -o setup.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

# 3. Bağlama (Link) Aşaması CRITICAL ORDER!
# boot.o kesinlikle EN BAŞTA olmalı ki multiboot header ilk baytlarda yer alsın!
ld -m elf_i386 -T linker.ld -o kernel.bin boot.o kernel.o setup.o

# 4. ISO Oluşturma
mkdir -p iso/boot/grub
cp kernel.bin iso/boot/kernel.bin

# grub.cfg oluşturma/kopyalama simülasyonu
cat << EOF > iso/boot/grub/grub.cfg
set timeout=0
set default=0

menuentry "Wind OS" {
    multiboot /boot/kernel.bin
    boot
}
EOF

grub-mkrescue -o windos.iso iso
echo "=== Başarılı: windos.iso mühürlendi! ==="
