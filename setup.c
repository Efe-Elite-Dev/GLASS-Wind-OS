#include "setup.h"

// Donanımsal Grafik Belleği Çözünürlük Sabitleri
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
uint8_t* const VIDEO_MEMORY = (uint8_t*)0xA0000;

// Palet Renk İndeksleri
#define COLOR_WIND_BG        16  // Nötr Gri Arka Plan
#define COLOR_WIND_CARD      17  // Saf Beyaz Panel
#define COLOR_WIND_TEXT      18  // Koyu Lacivert/Siyah Yazı
#define COLOR_WIND_PRIMARY   19  // Windland OS Mavisi (Butonlar)
#define COLOR_WIND_SWIRL     20  // Fırtına Turkuazı (Wind Efektleri)
#define COLOR_WIND_3D_LIGHT  21  // Parlayan Kenar Beyazı
#define COLOR_WIND_3D_DARK   22  // Derin Gölge Koyu Gri

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

// Kurulum Kademeleri (Tasarımların Birebir Akışı)
typedef enum {
    STAGE_WIND_COUNTRY = 0,    // "Bu doğru ülke mi?" Adımı
    STAGE_WIND_KEYBOARD,       // "Klavye Düzeni" Adımı
    STAGE_WIND_NETWORK,        // "Ağ Bağlantısı" Adımı
    STAGE_WIND_HOSTNAME,       // "Wind OS istasyonunuza bir ad verelim"
    STAGE_WIND_CUSTOMIZE,      // "Wind OS deneyiminizi özelleştirin"
    STAGE_WIND_COMPLETE
} SetupStage;

static SetupStage current_stage = STAGE_WIND_COUNTRY;
static int button_press_depth = 0;
static int wind_anim_frame = 0;

void setup_init_palette(void) {
    // Grafik kartı renk paletini Windland OS konseptine göre boyuyoruz
    outb(0x3C8, COLOR_WIND_BG);       outb(0x3C9, 58); outb(0x3C9, 59); outb(0x3C9, 61);
    outb(0x3C8, COLOR_WIND_CARD);     outb(0x3C9, 63); outb(0x3C9, 63); outb(0x3C9, 63);
    outb(0x3C8, COLOR_WIND_TEXT);     outb(0x3C9, 5);  outb(0x3C9, 10); outb(0x3C9, 20);
    outb(0x3C8, COLOR_WIND_PRIMARY);  outb(0x3C9, 0);  outb(0x3C9, 40); outb(0x3C9, 58);
    outb(0x3C8, COLOR_WIND_SWIRL);    outb(0x3C9, 20); outb(0x3C9, 55); outb(0x3C9, 55);
    outb(0x3C8, COLOR_WIND_3D_LIGHT); outb(0x3C9, 63); outb(0x3C9, 63); outb(0x3C9, 63);
    outb(0x3C8, COLOR_WIND_3D_DARK);  outb(0x3C9, 30); outb(0x3C9, 30); outb(0x3C9, 32);
}

void setup_put_pixel(int x, int y, uint8_t color) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        VIDEO_MEMORY[y * SCREEN_WIDTH + x] = color;
    }
}

void setup_draw_rect(int x, int y, int w, int h, uint8_t color) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            setup_put_pixel(x + j, y + i, color);
        }
    }
}

// Harika Kıvrımlı Rüzgarlı Fırtına Logoları Çizen Fonksiyon (Wind Swirls)
void draw_wind_swirl_vector(int cx, int cy, int size) {
    for (int i = 0; i < size; i++) {
        // Matematiksel dalga fonksiyonu ile pikselleri rüzgar gibi büküyoruz
        int offset_x = (i * i) / 20 + wind_anim_frame;
        int offset_y = i - (size / 2);
        setup_put_pixel(cx + offset_x, cy + offset_y, COLOR_WIND_SWIRL);
        setup_put_pixel(cx - offset_x, cy - offset_y, COLOR_WIND_TEXT);
        setup_put_pixel(cx + offset_y, cy - offset_x / 2, COLOR_WIND_SWIRL);
    }
}

// Fluent / 3D Hibrit Panel Çizici
void draw_window_card(int x, int y, int w, int h) {
    setup_draw_rect(x, y, w, h, COLOR_WIND_CARD);
    // İnce 3D gölgelendirmeyle havada durma (floating card) hissi veriyoruz
    for (int i = 0; i < w; i++) {
        setup_put_pixel(x + i, y + h, COLOR_WIND_3D_DARK);
        setup_put_pixel(x + i, y + h + 1, COLOR_WIND_3D_DARK);
    }
    for (int i = 0; i < h; i++) {
        setup_put_pixel(x + w, y + i, COLOR_WIND_3D_DARK);
        setup_put_pixel(x + w + 1, y + i, COLOR_WIND_3D_DARK);
    }
}

// Mekanik Çökme Animasyonuna Sahip Akıllı Buton Sürücüsü
void draw_responsive_button(int x, int y, int w, int h, const char* label) {
    (void)label;
    int depth = button_press_depth;
    setup_draw_rect(x, y, w, h, COLOR_WIND_3D_DARK); // Buton Arkası Boşluk
    setup_draw_rect(x + depth, y + depth, w - depth, h - depth, COLOR_WIND_PRIMARY);
}

void setup_render(void) {
    // 1. Windland OS Gradyan Esintili Arka Plan
    setup_draw_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_WIND_BG);
    
    // 2. Ana İşlem Kartı (Center Panel)
    draw_window_card(20, 15, 280, 170);

    // 3. Kademelere Göre Görsel Vektör ve Form Çizimleri (UI Ekran Görüntülerinle Birebir)
    switch (current_stage) {
        case STAGE_WIND_COUNTRY:
            draw_wind_swirl_vector(80, 90, 40); // "W" harfli fırtına girdabı
            setup_draw_rect(150, 40, 120, 15, COLOR_WIND_BG);
            setup_draw_rect(150, 60, 120, 15, COLOR_WIND_PRIMARY); // Seçili "Windland OS" barı
            setup_draw_rect(150, 80, 120, 15, COLOR_WIND_BG);
            break;
            
        case STAGE_WIND_KEYBOARD:
            // Klavye Matrisi Çizimi
            setup_draw_rect(50, 70, 60, 40, COLOR_WIND_BG);
            for(int k=0; k<4; k++) setup_draw_rect(55, 75 + (k*8), 50, 4, COLOR_WIND_TEXT);
            setup_draw_rect(150, 50, 120, 15, COLOR_WIND_PRIMARY); // "Türkçe Q" Seçimi
            break;
            
        case STAGE_WIND_NETWORK:
            // Wi-Fi Sinyal Vektör Çizimi
            draw_wind_swirl_vector(70, 90, 30);
            setup_draw_rect(140, 75, 130, 12, COLOR_WIND_BG); // Şifre Giriş Alanı (Gömülü)
            break;
            
        case STAGE_WIND_HOSTNAME:
            // Laptop ve Cihaz Adlandırma Alanı ("Station-alpha")
            setup_draw_rect(40, 80, 50, 35, COLOR_WIND_TEXT);
            setup_draw_rect(35, 115, 60, 5, COLOR_WIND_PRIMARY);
            setup_draw_rect(130, 85, 140, 15, COLOR_WIND_CARD); // Girdi kutusu
            setup_draw_rect(130, 100, 80, 2, COLOR_WIND_PRIMARY); // Focus Alt Çizgisi
            break;
            
        case STAGE_WIND_CUSTOMIZE:
            // Özelleştirme Checkboxları ("Creative Swirls", "Gaming Gusts")
            for(int i=0; i<3; i++) {
                setup_draw_rect(140, 45 + (i * 25), 10, 10, COLOR_WIND_BG);
                if (i == 0) setup_draw_rect(142, 47, 6, 6, COLOR_WIND_PRIMARY); // Checkbox İşaretli
            }
            break;
            
        default:
            // Kurulum Tamamlandı
            draw_wind_swirl_vector(160, 100, 60);
            break;
    }

    // Alt Navigasyon "Sonraki / İleri" Mekanik Butonu
    draw_responsive_button(220, 155, 65, 20, "Ileri");
}

void setup_delay(int count) {
    volatile int i = 0;
    for (i = 0; i < count * 8000; i++) {
        __asm__("nop");
    }
}

void trigger_next_stage(void) {
    // Buton basılma animasyonu (Mekanik Çöküş)
    for (button_press_depth = 0; button_press_depth <= 3; button_press_depth++) {
        setup_render();
        setup_delay(8);
    }
    
    // Rüzgar animasyonunu ilerlet ve kademe atla
    wind_anim_frame += 4;
    if (current_stage < STAGE_WIND_COMPLETE) {
        current_stage++;
    } else {
        current_stage = STAGE_WIND_COUNTRY; // Başa dön (Loop)
    }
    
    button_press_depth = 0;
    setup_render();
}

void setup_init(void) {
    setup_init_palette();
    setup_render();
}

void setup_handle_input(uint8_t scancode) {
    if (scancode == 0x1C) { // ENTER tuşuna her basıldığında sonraki sayfaya akar
        trigger_next_stage();
    }
}
