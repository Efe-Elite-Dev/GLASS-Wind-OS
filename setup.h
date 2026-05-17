#ifndef SETUP_H
#define SETUP_H

#include <stdint.h>

// Kurulum Kademeleri - Tek bir yerde tanımlı
typedef enum {
    STAGE_WIND_COUNTRY = 0,    // "Bu doğru ülke mi?" Adımı
    STAGE_WIND_KEYBOARD,       // "Klavye Düzeni" Adımı
    STAGE_WIND_NETWORK,        // "Ağ Bağlantısı" Adımı
    STAGE_WIND_HOSTNAME,       // "Wind OS istasyonunuza bir ad verelim"
    STAGE_WIND_CUSTOMIZE,      // "Wind OS deneyiminizi özelleştirin"
    STAGE_WIND_COMPLETE
} SetupStage;

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 200

// Renk Paleti İndeksleri
#define COLOR_WIND_BG        16  // Nötr Gri Arka Plan
#define COLOR_WIND_CARD      17  // Saf Beyaz Panel
#define COLOR_WIND_TEXT      18  // Koyu Lacivert/Siyah Yazı
#define COLOR_WIND_PRIMARY   19  // Windland OS Mavisi (Butonlar)
#define COLOR_WIND_SWIRL     20  // Fırtına Turkuazı (Wind Efektleri)
#define COLOR_WIND_3D_LIGHT  21  // Parlayan Kenar Beyazı
#define COLOR_WIND_3D_DARK   22  // Derin Gölge Koyu Gri

void setup_init(void);
void setup_render(void);
void setup_handle_input(uint8_t scancode);

#endif
