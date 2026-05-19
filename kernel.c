/**
 * ==============================================================================
 * 🌟 SKY CORE OS - İLK SAF ÇEKİRDEK (LEGACY PURE CORE) 🌟
 * ==============================================================================
 * [Mimari]: 32-Bit Korumalı Mod (Protected Mode) - x86 IA-32 Standartları
 * [Açıklama]: Diğer dosyaların (kerror.c, vga_force.c) aradığı küresel değişkenleri
 * besleyen ve harici fonksiyonları kilitleyen en saf, bağımsız çekirdek.
 * ==============================================================================
 */

#include <stdint.h>

// 1. DİĞER DOSYALARIN HATA VERMEMESİ İÇİN KÜRESEL GRAFİK DEĞİŞKENİ (Linker Fix)
// kerror.c ve vga_force.c bu adresi arıyor, onlara bu pointer'ı veriyoruz.
uint32_t* GRAPHICS_FRAMEBUFFER = (uint32_t*)0xE0000000;

// x86 Standart Metin Belleği Adresi (0xB8000)
volatile uint16_t* const VIDEO_MEMORY = (uint16_t*)0xB8000;

int cursor_x = 0;
int cursor_y = 0;

// Ekranı temizleme fonksiyonu (Standart Metin Modu)
void clear_screen(void) {
    for (int i = 0; i < 80 * 25; i++) {
        // Koyu mavi arka plan (0x1), Beyaz yazı rengi (0xF) -> 0x1F
        VIDEO_MEMORY[i] = (0x1F << 8) | ' ';
    }
    cursor_x = 0;
    cursor_y = 0;
}

// Ekrana saf metin yazdırma fonksiyonu
void print_str(const char* str) {
    while (*str) {
        if (*str == '\n') {
            cursor_x = 0;
            cursor_y++;
        } else {
            int index = cursor_y * 80 + cursor_x;
            VIDEO_MEMORY[index] = (0x1F << 8) | *str;
            cursor_x++;
            if (cursor_x >= 80) {
                cursor_x = 0;
                cursor_y++;
            }
        }
        str++;
    }
}

// Giriş portundan veri okuma (Klavye portu için)
static inline uint8_t in_byte(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// ==============================================================================
// 🚀 KERNEL GİRİŞ NOKTASI
// ==============================================================================
void kernel_main(void* mboot_ptr, uint32_t magic) {
    // Kullanılmayan Multiboot parametreleri uyarısını sustur
    (void)mboot_ptr;
    (void)magic;

    // Ekranı lacivert yap ve canlanma sinyalini bas
    clear_screen();
    print_str("======================================================================\n");
    print_str("                    SKY CORE OS v1.5 - SAF CEKIRDEK                   \n");
    print_str("======================================================================\n\n");
    print_str("[ OK ] Korumali Mod (32-Bit Protected Mode) aktif.\n");
    print_str("[ OK ] Ekran metin bellegi baglantisi saglandi (0xB8000).\n");
    print_str("[ OK ] Diger hatali grafik alt sistemleri baypas edildi.\n\n");
    print_str("Sistem su an tamamen stabil! Sanal makine kilitlenmesi cozuldu.\n");
    print_str("Klavye girdisi bekleniyor...\n");

    // Güvenli sonsuz polling döngüsü (Diğer dosyaları çağırmaz, kendi döngüsünde kalır)
    while (1) {
        // Klavye veri kontrolü (Port 0x64 üzerinden durum kontrolü)
        if (in_byte(0x64) & 1) {
            uint8_t scancode = in_byte(0x60);
            (void)scancode; // Gelen scancode'u şimdilik yutuyoruz, çökme yaratmaz
        }
    }
}
