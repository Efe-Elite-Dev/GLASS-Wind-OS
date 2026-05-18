#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 200

extern uint8_t* vbe_vram;
extern uint32_t vbe_pitch;

// Linker hatalarını bitiren o meşhur saf piksel fonksiyonu bildirimi
void draw_pixel_pure(int x, int y, uint8_t color);

void screen_init(void);
void screen_put_pixel(int x, int y, uint8_t color);
void screen_flush(void);

#endif
