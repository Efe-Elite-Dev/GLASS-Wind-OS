#ifndef SKY_CORE_H
#define SKY_CORE_H
#include <stdint.h>

// Global Grafik Değişkenleri
extern uint32_t* FRAMEBUFFER;
extern int SCREEN_W;
extern int SCREEN_H;

// Çizim Fonksiyonları
void draw_pixel(int x, int y, uint32_t color);
void draw_rect(int x, int y, int w, int h, uint32_t color);
void draw_rounded_rect(int x, int y, int w, int h, int radius, uint32_t color);

#endif
