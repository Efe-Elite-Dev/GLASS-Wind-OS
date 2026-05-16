#!/bin/bash
# Hata olursa anında göster ama derlemeyi bozmamak için temiz ilerle
set -e

echo "==> Sky OS Mimarisi ile Wind OS Derleniyor..."

# 1. Önceki kalıntıları tertemiz yap
rm -rf isodir windos.iso kernel.bin *.o

# 2. ISO klasör mimarisini kusursuz kur
mkdir -p isodir/boot/grub

# 3. Bootloader'ı derle (Multiboot)
echo "==> Bootloader derleniyor..."
nasm -f elf32 boot.asm -o boot.o

# 4. Wind OS AI Çekirdeği ve Alt Sistemleri Derle
echo "==> Wind OS C modülleri derleniyor..."
gcc -m32 -ffreestanding -O2 -Wall -Wextra -c kernel.c -o kernel.o
gcc -m32 -ffreestanding -O2 -Wall -Wextra -c gui.c -o gui.o
gcc -m32 -ffreestanding -O2 -Wall -Wextra -c exe_subsystem.c -o exe_subsystem.o
gcc -m32 -ffreestanding -O2 -Wall -Wextra -c ai_subsystem.c -o ai_subsystem.o
gcc -m32 -ffreestanding -O2 -Wall -Wextra -c mouse.c -o mouse.o
gcc -m32 -ffreestanding -O2 -Wall -Wextra -c keyboard.c -o keyboard.o
gcc -m32 -ffreestanding -O2 -Wall -Wextra -c wind_subsystem.c -o wind_subsystem.o
gcc -m32 -ffreestanding -O2 -Wall -Wextra -c screen.c -o screen.o
gcc -m32 -ffreestanding -O2 -Wall -Wextra -c idt.c -o idt.o
gcc -m32 -ffreestanding -O2 -Wall -Wextra -c deb_subsystem.c -o deb_subsystem.o

# 5. Parçaları Linker ile Birleştir
echo "==> Linker ile çekirdek birleştiriliyor..."
gcc -m32 -T linker.ld -nostdlib -no-pie -o kernel.bin boot.o kernel.o gui.o exe_subsystem.o ai_subsystem.o mouse.o keyboard.o wind_subsystem.o screen.o idt.o deb_subsystem.o

# 6. Dosyaları ISO'ya Aktar ve GRUB Ayarla
cp kernel.bin isodir/boot/kernel.bin

cat << 'EOF' > isodir/boot/grub/grub.cfg
set timeout=0
set default=0
menuentry "Wind OS - AI Core (Powered by Sky OS Engine)" {
    multiboot /boot/kernel.bin
    boot
}
EOF

# 7. ISO'yu Hatasız Mühürle
echo "==> grub-mkrescue ile nihai ISO basılıyor..."
grub-mkrescue -o windos.iso isodir

echo "==> [BAŞARILI] Wind OS ISO dosyası sorunsuz şekilde oluşturuldu!"
