#ifndef SETUP_H
#define SETUP_H

#include <stdint.h>

// Kurulum Ekranı Aşamaları (State Machine)
typedef enum {
    STAGE_COUNTRY,       // Bu doğru ülke mi?
    STAGE_KEYBOARD,      // Klavye Düzeni
    STAGE_NETWORK,       // Ağ Bağlantısı
    STAGE_HOSTNAME,      // Wind OS istasyonunuza bir ad verelim
    STAGE_CUSTOMIZE,     // Wind OS deneyiminizi özelleştirin
    STAGE_COMPLETE       // Kurulum Tamamlandı
} SetupStage;

// VGA Grafik Tanımları
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 200
#define VIDEO_MEMORY  ((uint8_t*)0xA0000)

// Özel Renk İndeksleri (Paleti ezerek atayacağız)
#define COLOR_WIND_BG        16  // Arka plan yumuşak açık gri/mavi tonu
#define COLOR_WIND_CARD      17  // Kurulum kartları için saf beyaz
#define COLOR_WIND_TEXT      18  // Başlıklar ve yazılar için koyu lacivert
#define COLOR_WIND_PRIMARY   19  // Butonlar ve aktif elemanlar için parlak modern mavi
#define COLOR_WIND_TURQ      20  // Logodaki ve detaylardaki turkuaz esinti
#define COLOR_WIND_DARK_LINE 21  // Logodaki ana hatlar ve koyu dalgalar

// Dışarıya Açılan Fonksiyon Prototipleri
void setup_init(void);
void setup_render(void);
void setup_handle_input(uint8_t scancode);

#endif // SETUP_H
