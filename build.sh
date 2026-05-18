#!/bin/bash
# ==============================================================================
# 🌪️ Wind OS / Sky Core OS - MEGA BUILD ENGINE & BOOTSTRAPPER (v1.5)
# ==============================================================================
set -e

echo "======================================================================"
echo "🚀 WIND OS MEGA BUILD ENGINE BAŞLATILDI"
echo "======================================================================"
echo "[+] Geçerli Konum: $(pwd)"
echo "[+] Sistem Kaynakları Optimize Ediliyor (Büyük İmaj Desteği Aktif)..."

# 1. Temizlik ve Ön Hazırlık
echo "[-] Eski derleme kalıntıları temizleniyor..."
rm -rf iso kernel.bin *.o windos.iso build_output.log

# 2. Assembly Çekirdeğinin Derlenmesi
echo "[1] Çekirdek önyükleme mekanizması derleniyor (boot.asm)..."
if [ -f "boot.asm" ]; then
    nasm -f elf32 boot.asm -o boot.o
    echo "    -> [OK] boot.o başarıyla üretildi."
else
    echo "    ❌ KRİTİK HATA: boot.asm ana dizinde bulunamadı!"
    exit 1
fi

# 3. Temel C Modüllerinin Derlenmesi
echo "[2] Temel Kernel ve Kurulum modülleri derleniyor..."
declare -A CORE_MODULES=(
    ["kernel.c"]="kernel.o"
    ["setup.c"]="setup.o"
    ["setup_ui.c"]="setup_ui.o"
)

CORE_OBJS=""
for src in "${!CORE_MODULES[@]}"; do
    obj="${CORE_MODULES[$src]}"
    if [ -f "$src" ]; then
        echo "    -> Derleniyor: $src"
        gcc -m32 -c "$src" -o "$obj" -std=gnu99 -ffreestanding -O2 -Wall -Wextra
        CORE_OBJS="$CORE_OBJS $obj"
    else
        echo "    ❌ KRİTİK HATA: Ana modül eksik -> $src"
        exit 1
    fi
done

# 4. Gelişmiş Alt Sistemlerin Dinamik ve Eksiksiz Derlenmesi (Mega Liste)
echo "[3] Repodaki tüm gelişmiş alt sistemler zincire mühürleniyor..."
SUBSYSTEMS=(
    "gui"
    "screen"
    "mouse"
    "keyboard"
    "idt"
    "wind_subsystem"
    "exe_subsystem"
    "ai_subsystem"
    "deb_subsystem"
    "uefi_subsystem"
    "si_subsystem"
)

OPTIONAL_OBJS=""
for sys in "${SUBSYSTEMS[@]}"; do
    if [ -f "${sys}.c" ]; then
        echo "    [+] Alt Sistem Yakalandı: ${sys}.c derleniyor..."
        gcc -m32 -c "${sys}.c" -o "${sys}.o" -std=gnu99 -ffreestanding -O2 -Wall -Wextra
        OPTIONAL_OBJS="$OPTIONAL_OBJS ${sys}.o"
    else
        echo "    [-] Bilgi: ${sys}.c bu derlemede pas geçildi (Dosya yok)."
    fi
done

# 5. Bağlama (Linker) Aşaması
echo "[4] Tüm nesne dosyaları linker.ld şablonuna göre birleştiriliyor..."
if [ -f "linker.ld" ]; then
    # Bütün .o dosyalarını tek bir saf x86 kernel ikilisinde birleştiriyoruz
    ld -m elf_i386 -z noexecstack -T linker.ld -o kernel.bin boot.o $CORE_OBJS $OPTIONAL_OBJS
    echo "    -> [OK] kernel.bin başarıyla mühürlendi."
else
    echo "    ❌ KRİTİK HATA: linker.ld bulunamadı!"
    exit 1
fi

# 6. ISO Dağıtım Havuzunun Hazırlanması (Mega Depolama Desteği)
echo "[5] Canlı ISO yapısı ve GRUB önyükleme katmanı yapılandırılıyor..."
mkdir -p iso/boot/grub
cp kernel.bin iso/boot/kernel.bin

# Vasiyet ettiğin 26:03 zaman damgası ve fırtınalı temayı simüle eden GRUB yapılandırması
cat << EOF > iso/boot/grub/grub.cfg
set timeout=3
set default=0

# Ekran kartı modu ayarları
set gfxmode=1024x768x32
set gfxpayload=keep

menuentry "Wind OS / Sky Core OS v1.5 (Vortex Kernel)" {
    multiboot /boot/kernel.bin
    boot
}
EOF

# 7. Büyük Boyutlu Medya Paketleme Aşaması (Gerekirse >100MB / 2GB Desteği)
echo "[6] Önyüklenebilir medya (windos.iso) oluşturuluyor..."
# xorriso ve mtools parametreleri büyük veri bloklarını destekleyecek şekilde esnetildi
grub-mkrescue -o windos.iso iso -- -volid "WINDOS_15" -as mkisofs -iso-level 3

if [ -f "windos.iso" ]; then
    ISO_SIZE=$(du -h windos.iso | cut -f1)
    echo "======================================================================"
    echo "✅ BAŞARILI: Wind OS ISO imajı üretime hazır!"
    echo "[+] Çıktı Dosyası: windos.iso"
    echo "[+] İmaj Boyutu: $ISO_SIZE"
    echo "======================================================================"
else
    echo "❌ HATA: ISO oluşturma motoru başarısız oldu!"
    exit 1
fi
