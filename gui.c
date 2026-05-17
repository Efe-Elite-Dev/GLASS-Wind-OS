#include "gui.h"
#include "setup.h" // Kurulum renk tanımlarına erişim için

// Grafik Bellek Tanımları (Çakışmasız ham pointer)
#define VGA_SCREEN_WIDTH  320
#define VGA_SCREEN_HEIGHT 200
#define VGA_GRAPHICS_MEM  ((uint8_t*)0xA0000)

// LINKER HATASINI ÇÖZEN SAF PİKSEL SÜRÜCÜSÜ (PURE PIXEL DRIVER)
// gui.o içindeki tüm 'draw_pixel_pure' çağrılarını doğrudan buraya bağlıyoruz
static inline void draw_pixel_pure(int x, int y, uint8_t color) {
    if (x >= 0 && x < VGA_SCREEN_WIDTH && y >= 0 && y < VGA_SCREEN_HEIGHT) {
        VGA_GRAPHICS_MEM[y * VGA_SCREEN_WIDTH + x] = color;
    }
}

// Temel Düz Dikdörtgen Çizici
void draw_rect_pure(int x, int y, int w, int h, uint8_t color) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            draw_pixel_pure(x + j, y + i, color);
        }
    }
}

// Saf ve Hızlı Pencere Çizici (draw_window_pure)
void draw_window_pure(int x, int y, int w, int h, const char* title) {
    (void)title; // Şimdilik başlık metni uyarısını pass geçiyoruz

    // 1. Pencere Arka Plan Gövdesi (Beyaz panel hissi)
    draw_rect_pure(x, y, w, h, COLOR_WIND_CARD);

    // 2. Klasik 3D Pencere Çerçeve Efektleri (Kenarlıklar)
    // Üst ve Sol parlaklık çizgileri
    for (int i = 0; i < w; i++) draw_pixel_pure(x + i, y, COLOR_WIND_3D_LIGHT);
    for (int i = 0; i < h; i++) draw_pixel_pure(x, y + i, COLOR_WIND_3D_LIGHT);

    // Alt ve Sağ gölge çizgileri
    for (int i = 0; i < w; i++) draw_pixel_pure(x + i, y + h - 1, COLOR_WIND_3D_DARK);
    for (int i = 0; i < h; i++) draw_pixel_pure(x + w - 1, y + i, COLOR_WIND_3D_DARK);

    // 3. Pencere Üst Barı (Title Bar - Windland Mavisi)
    draw_rect_pure(x + 2, y + 2, w - 4, 12, COLOR_WIND_PRIMARY);
}

// GUI Alt Sistemini Başlatma Fonksiyonu
void gui_init(void) {
    // Masaüstünü temizle
    draw_rect_pure(0, 0, VGA_SCREEN_WIDTH, VGA_SCREEN_HEIGHT, COLOR_WIND_BG);
    
    // Test amaçlı bir Wind OS Saf Penceresi fırlat
    draw_window_pure(40, 30, 240, 140, "Wind OS System");
}
