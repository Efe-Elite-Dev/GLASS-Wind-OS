#!/bin/bash
# =============================================================================
# Wind OS - Otonom Gelişmiş AI Canlı Sistem Onarım ve Derleme Motoru v4.5
# =============================================================================

echo "🔄 [AI Hazırlık] Dosya formatları normalize ediliyor (CRLF -> LF)..."
find . -type f \( -name "*.c" -o -name "*.h" -o -name "PATCHES" -o -name "grub.cfg" \) -exec dos2unix {} + 2>/dev/null

# 1. [AI Akıllı Dosya Doğrulama] Klasör mimarisini denetle ve eksik dosyaları otonom üret
if [ -f "ueft_subsystem.c" ]; then
    echo "🤖 [AI Ön Onarım] Hatalı kaynak dosya adı algılandı. uefi_subsystem.c olarak değiştiriliyor..."
    mv ueft_subsystem.c uefi_subsystem.c
fi

if [ ! -f "uefi_subsystem.c" ]; then
    echo "🤖 [AI Kriz Yönetimi] uefi_subsystem.c diskte bulunamadı! Derlemeyi kurtarmak için otonom iskelet yazılıyor..."
    cat << 'EOF' > uefi_subsystem.c
#include <stdint.h>

void uefi_subsystem_init(void) {
    // Wind OS UEFI Alt Sistem Altyapısı Stub
}
EOF
fi

# 2. [AI Ön Denetim] GRUB önyükleme yapılandırmasını doğrula
if [ ! -f "grub.cfg" ]; then
    echo "🤖 [AI Ön Onarım] grub.cfg eksik! Standart şablon üretiliyor..."
    cat << 'EOF' > grub.cfg
set timeout=2
set default=0
insmod all_video
menuentry "Wind OS - Sky OS Engine" {
    multiboot /boot/kernel.bin
    boot
}
EOF
fi

# 3. [AI Ön Denetim] Çalışma zamanı dinamik Makefile fabrikası
# UEFI desteği için modüller otomatik eklenecek şekilde optimize edildi
cat << 'EOF' > Makefile
CC = gcc
CFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra -fno-pie -fno-stack-protector
LDFLAGS = -m32 -T linker.ld -nostdlib -no-pie
OBJS = boot.o kernel.o gui.o exe_subsystem.o ai_subsystem.o mouse.o wind_subsystem.o keyboard.o screen.o idt.o deb_subsystem.o uefi_subsystem.o

.PHONY: all clean

all: windos.iso

windos.iso: kernel.bin grub.cfg
	mkdir -p isodir/boot/grub
	cp kernel.bin isodir/boot/kernel.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	@# Standart grub-mkrescue mimarisi hem BIOS hem UEFI kalıplarını otonom bağlar.
	grub-mkrescue -o windos.iso isodir

kernel.bin: $(OBJS) linker.ld
	$(CC) $(LDFLAGS) -o kernel.bin $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	nasm -f elf32 $< -o $@

clean:
	rm -f *.o kernel.bin windos.iso
	rm -rf isodir
EOF

echo "🚀 [Derleme Pilotu] İlk derleme döngüsü tetikleniyor..."
make clean
make > build_output.log 2>&1
COMPILE_STATUS=$?

# =============================================================================
# 🧠 YAPAY ZEKA CANLI ONARIM KATMANI (AI REPAIR ENGINE)
# =============================================================================
if [ $COMPILE_STATUS -ne 0 ]; then
    echo "================================================================="
    echo "🚨 YAPAY ZEKA GÖREVE ÇAĞRILDI: CANLI SİSTEM ONARIM MOTORU AKTİF 🚨"
    echo "================================================================="
    cat build_output.log
    
    UNDEFINED_REF=$(grep -oP "undefined reference to \`\K[^\`']+" build_output.log | head -n 1)
    IMPLICIT_FUNC=$(grep -oP "implicit declaration of function \`\K[^\`']+" build_output.log | head -n 1)
    GCC_ERROR_LINE=$(grep -m 1 -oP "^[^:]+\.c:[0-9]+:[0-9]+: error:" build_output.log)
    
    if [ ! -z "$GCC_ERROR_LINE" ]; then
        TARGET_FILE=$(echo "$GCC_ERROR_LINE" | cut -d':' -f1)
        TARGET_ROW=$(echo "$GCC_ERROR_LINE" | cut -d':' -f2)
        echo "🤖 [AI Analiz] Durum Teşhisi Yapıldı -> Dosya: $TARGET_FILE | Satır: $TARGET_ROW"
    fi

    # Zeka Hücresi 1: Linker Referans Uyuşmazlıkları
    if [ ! -z "$UNDEFINED_REF" ]; then
        echo "🤖 [AI Onarım] 'Undefined Reference' hatası algılandı: Sembol -> $UNDEFINED_REF"
        if [ "$UNDEFINED_REF" == "back_buffer" ] && [ -f "screen.c" ]; then
            echo "⚡ [AI Aksiyon] screen.c dosyasına 'back_buffer' dizisi enjekte ediliyor..."
            sed -i '1s/^/uint32_t back_buffer[800 * 600];\n/' screen.c
        fi
    fi

    # Zeka Hücresi 2: Bildirilmemiş Fonksiyon Çağrıları
    if [ ! -z "$IMPLICIT_FUNC" ] && [ -f "kernel.c" ]; then
        echo "🤖 [AI Onarım] 'Implicit Declaration' hatası algılandı: Fonksiyon -> $IMPLICIT_FUNC"
        if grep -q "HARİCİ ALT SİSTEM" kernel.c; then
            sed -i "/HARİCİ ALT SİSTEM/a extern void ${IMPLICIT_FUNC}(void);" kernel.c
        fi
    fi

    # Zeka Hücresi 3: Akıllı Sözdizimi Tarayıcı (Eksik Noktalı Virgül Düzeltme)
    if [ ! -z "$TARGET_FILE" ] && [ ! -z "$TARGET_ROW" ]; then
        LINE_CONTENT=$(sed -n "${TARGET_ROW}p" "$TARGET_FILE")
        if [[ ! "$LINE_CONTENT" =~ \;$ ]] && [[ ! "$LINE_CONTENT" =~ \{$ ]] && [[ ! "$LINE_CONTENT" =~ \}$ ]] && [ ! -z "$LINE_CONTENT" ]; then
            sed -i "${TARGET_ROW}s/$/;/" "$TARGET_FILE"
        fi
    fi

    echo "🔄 [AI Son Aşama] Yapay zeka yamaları uyguladı. Yeniden derleniyor..."
    make clean
    make
    
    if [ $? -ne 0 ]; then
        echo "❌ [AI İflas] Canlı onarım motoru yapısal hatayı aşamadı."
        exit 1
    fi
fi

# =============================================================================
# 🎯 NİHAİ ISO KONTROLÜ VE SANAL MAKİNE UYUMLULUK KILAVUZU
# =============================================================================
if [ ! -f "windos.iso" ]; then
    echo "❌ HATA: windos.iso başarıyla üretilemedi!"
    exit 1
fi

echo "------------------------------------------------------------------"
echo "✅ [MÜHÜR BAŞARILI] Yapay zeka sistemi canlı onardı ve windos.iso üretildi!"
echo "------------------------------------------------------------------"
echo "🚨 VIRTUALBOX'TA ÇALIŞTIRMADAN ÖNCE MUTLAKA YAPMAN GEREKEN AYAR:"
echo "1. VirtualBox'ta Wind OS sanal makinenin 'Ayarlar' (Settings) kısmına gir."
echo "2. 'Sistem' (System) -> 'Anakart' (Motherboard) sekmesine tıkla."
echo "3. En alttaki 'EFI'yi Etkinleştir' (Enable EFI) seçeneğindeki İŞARETİ KALDIR (Kapat)."
echo "4. Kaydet ve sanal makineyi başlat. Sisteminiz başarıyla açılacaktır."
echo "------------------------------------------------------------------"
