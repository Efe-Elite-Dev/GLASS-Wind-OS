#ifndef SKY_CORE_H
#define SKY_CORE_H

#include <stdint.h>

// Global değişkenler
extern uint32_t* FRAMEBUFFER;
extern int SCREEN_W;
extern int SCREEN_H;

// Fonksiyonlar
void draw_pixel(int x, int y, uint32_t color);
void draw_rect(int x, int y, int w, int h, uint32_t color);
void draw_rounded_rect(int x, int y, int w, int h, int radius, uint32_t color);
void render_ui(void);
void force_graphics_hardware(void);
void kpanic(uint8_t error_code, const char* message);

#endif
