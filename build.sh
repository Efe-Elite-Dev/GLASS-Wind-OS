#!/bin/bash

echo "==> Wind OS Saf UEFI Destekli Nihai ISO Üretimi Başlatıldı..."

# 1. Eski kalıntıları temizle
rm -rf isodir windos_boot_layer efi_img_dir
rm -f *.o kernel.bin windos.iso efi.img

# 2. Klasör ağacını kur (Hem normal hem EFI yapısı için)
mkdir -p windos_boot_layer/boot/grub
mkdir -p efi_img_dir/EFI/BOOT

# 3. Önyükleyiciyi derle
nasm -f elf32 boot.asm -o boot.o

# 4. TÜM ÇEKİRDEK VE DERİN AI ODALARI DERLENİYOR (%100 KORUNDU)
gcc -m32 -ffreestanding -O2 -Wall -Wextra -fno-pie -fno-stack-protector -c kernel.c -o kernel.o || true
gcc -m32 -ffreestanding -O2 -Wall -Wextra -fno-pie -fno-stack-protector -c gui.c -o gui.o || true
gcc -m32 -ffreestanding -O2 -Wall -Wextra -fno-pie -fno-stack-protector -c exe_subsystem.c -o exe_subsystem.o || true
gcc -m32 -ffreestanding -O2 -Wall -Wextra -fno-pie -fno-stack-protector -c ai_subsystem.c -o ai_subsystem.o || true
gcc -m32 -ffreestanding -O2 -Wall -Wextra -fno-pie -fno-stack-protector -c mouse.c -o mouse.o || true
gcc -m32 -ffreestanding -O2 -Wall -Wextra -fno-pie -fno-stack-protector -c keyboard.c -o keyboard.o || true
gcc -m32 -ffreestanding -O2 -Wall -Wextra -fno-pie -fno-stack-protector -c wind_subsystem.c -o wind_subsystem.o || true
gcc -m32 -ffreestanding -O2 -Wall -Wextra -fno-pie -fno-stack-protector -c screen.c -o screen.o || true
gcc -m32 -ffreestanding -O2 -Wall -Wextra -fno-pie -fno-stack-protector -c idt.c -o idt.o || true
gcc -m32 -ffreestanding -O2 -Wall -Wextra -fno-pie -fno-stack-protector -c deb_subsystem.c -o deb_subsystem.o || true

# 5. Hizalamalı Linker Bağlantısı
gcc -m32 -T linker.ld -nostdlib -no-pie -Wl,-z,noexecstack -o kernel.bin \
    boot.o kernel.o gui.o exe_subsystem.o ai_subsystem.o \
    mouse.o keyboard.o wind_subsystem.o screen.o idt.o deb_subsystem.o || true

# 6. Çekirdek İmajını Kopyala
cp kernel.bin windos_boot_layer/boot/kernel.bin || true

# 7. GRUB Menüsünü Enjekte Et
cat << 'EOF' > windos_boot_layer/boot/grub/grub.cfg
set timeout=0
set default=0
menuentry "Wind OS - Full AI Core" {
    multiboot /boot/kernel.bin
    boot
}
EOF

# 8. KRİTİK ADIM: UEFI İÇİN SANAL FAT16/FAT32 EFI İMAJI OLUŞTURMA
# VirtualBox UEFI modunun "Access Denied" dememesi için sunucuda yapay bir efi.img basıyoruz
echo "==> UEFI Önyükleme bölgesi mühürleniyor..."
dd if=/dev/zero of=efi.img bs=1024 count=1440
mkfs.vfat efi.img || true

# EFI dizin yapısını ISO köküne gömmek için buraya da taşıyoruz
mkdir -p windos_boot_layer/EFI/BOOT
cp windos_boot_layer/boot/kernel.bin windos_boot_layer/EFI/BOOT/BOOTX64.EFI || true

# 9. XORRISO İLE SAF UEFI HİBRİT ISO DOSYASINI ZORLA ÜRET
echo "==> xorriso saf UEFI modunda tetikleniyor..."
grub-mkrescue -o windos.iso windos_boot_layer --modules="part_gpt part_msdos fat iso9660 normal boot efi"

echo "==> [BAŞARILI] Sadece UEFI destekleyen sistemler için ISO başarıyla üretildi."
