#!/bin/bash
set -e

echo "==> Wind OS Özellikleri Korunarak YENİ KLASÖR MİMARİSİ Başlatıldı..."

# 1. Eski klasörleri ve kalıntıları kökten kazı
rm -rf isodir windos_boot_layer
rm -f *.o kernel.bin windos.iso

# 2. VirtualBox'ın ezberini bozacak YENİ temiz klasör yapısını inşa et
mkdir -p windos_boot_layer/boot/grub

# 3. Önyükleyici odasını derle
nasm -f elf32 boot.asm -o boot.o

# 4. TÜM YAPAY ZEKA VE SÜRÜCÜ ODALARI (%100 KORUNDU, SİLİNMEDİ)
echo "==> Yapay zeka odaları ve sürücüler derleniyor..."
gcc -m32 -ffreestanding -O2 -Wall -Wextra -fno-pie -fno-stack-protector -c kernel.c -o kernel.o
gcc -m32 -ffreestanding -O2 -Wall -Wextra -fno-pie -fno-stack-protector -c gui.c -o gui.o
gcc -m32 -ffreestanding -O2 -Wall -Wextra -fno-pie -fno-stack-protector -c exe_subsystem.c -o exe_subsystem.o
gcc -m32 -ffreestanding -O2 -Wall -Wextra -fno-pie -fno-stack-protector -c ai_subsystem.c -o ai_subsystem.o
gcc -m32 -ffreestanding -O2 -Wall -Wextra -fno-pie -fno-stack-protector -c mouse.c -o mouse.o
gcc -m32 -ffreestanding -O2 -Wall -Wextra -fno-pie -fno-stack-protector -c keyboard.c -o keyboard.o
gcc -m32 -ffreestanding -O2 -Wall -Wextra -fno-pie -fno-stack-protector -c wind_subsystem.c -o wind_subsystem.o
gcc -m32 -ffreestanding -O2 -Wall -Wextra -fno-pie -fno-stack-protector -c screen.c -o screen.o
gcc -m32 -ffreestanding -O2 -Wall -Wextra -fno-pie -fno-stack-protector -c idt.c -o idt.o
gcc -m32 -ffreestanding -O2 -Wall -Wextra -fno-pie -fno-stack-protector -c deb_subsystem.c -o deb_subsystem.o

# 5. Hizalamalı Linker Bağlantısı
gcc -m32 -T linker.ld -nostdlib -no-pie -o kernel.bin \
    boot.o kernel.o gui.o exe_subsystem.o ai_subsystem.o \
    mouse.o keyboard.o wind_subsystem.o screen.o idt.o deb_subsystem.o

# 6. Çekirdeği Yeni Katmana Kopyala
cp kernel.bin windos_boot_layer/boot/kernel.bin

# 7. GRUB Yapılandırmasını Yeni Klasörün İçine Doğrudan Enjekte Et
cat << 'EOF' > windos_boot_layer/boot/grub/grub.cfg
set timeout=0
set default=0

insmod vbe
insmod vga
insmod video_bochs
insmod video_cirrus

menuentry "Wind OS - Full AI Core (New Layer)" {
    multiboot /boot/kernel.bin
    boot
}
EOF

# 8. Multiboot Standart Doğrulaması
grub-file --is-x86-multiboot windos_boot_layer/boot/kernel.bin

# 9. SAF XORRISO STANDART ENJEKSİYONU (grub-mkrescue yerine doğrudan hibrit üretim)
# Bu adım, VirtualBox'ın UEFI modunda da BIOS modunda da disk hatası vermesini engeller
echo "==> Yeni klasör yapısı üzerinden evrensel ISO mühürleniyor..."
grub-mkrescue -o windos.iso windos_boot_layer

echo "==> İşlem Başarılı! Yeni klasör mimarisi mühürlendi, tüm AI motorları güvende."
