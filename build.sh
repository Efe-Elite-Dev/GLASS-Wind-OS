#!/bin/bash
# ======================================================================
# 🚀 SKY CORE OS / WIND OS MEGA BUILD ENGINE
# ======================================================================

set -e # Herhangi bir adım hata verirse betiği hemen durdur

echo "[-] Eski derleme kalıntıları temizleniyor..."
rm -rf *.o kernel.bin os_image.iso iso_root

echo "[1] Çekirdek önyükleme mekanizması derleniyor (boot.asm)..."
nasm -f elf32 boot.asm -o boot.o

echo "[2] Çekirdek ve tüm alt sistemler derleniyor..."
# Klasördeki tüm .c dosyalarını tek tek döngüyle 32-bit ELF nesne dosyasına çeviriyoruz
for c_file in *.c; do
    if [ -f "$c_file" ]; then
        obj_file="${c_file%.c}.o"
        echo "    -> $c_file derleniyor..."
        gcc -m32 -c "$c_file" -o "$obj_file" -std=gnu99 -ffreestanding -O2 -Wall -Wextra
    fi
done

echo "[3] Tüm nesne dosyaları linker.ld şablonuna göre birleştiriliyor..."
# boot.o ve klasörde derlenmiş ne kadar .o dosyası varsa hepsini linker'a gönderiyoruz
ld -m elf_i386 -T linker.ld -o kernel.bin boot.o *.o --no-warn-rwx-segments

echo "[4] Boot edilebilir ISO imajı paketleniyor..."
# GRUB standartlarına uygun klasör yapısını kökten tertemiz inşa ediyoruz
mkdir -p iso_root/boot/grub

# Derlenen çekirdeği boot klasörünün altına taşıyoruz
cp kernel.bin iso_root/boot/kernel.bin

# Eksik olma ihtimaline karşı tertemiz bir grub.cfg oluşturuyoruz
cat << 'EOF' > iso_root/boot/grub/grub.cfg
set timeout=0
set default=0

menuentry "Sky Core OS / Wind OS" {
    multiboot /boot/kernel.bin
    boot
}
EOF

# xorriso ve GRUB2 uyuşmazlığını aşmak için resmi kurtarma komutunu tetikliyoruz
grub-mkrescue -o os_image.iso iso_root

echo "======================================================================"
echo "🎉 BAŞARILI: Sky Core OS ISO imajı (os_image.iso) başarıyla üretildi!"
echo "======================================================================"
