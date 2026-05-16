#ifndef WIND_SUBSYSTEM_H
#define WIND_SUBSYSTEM_H

#include <stdint.h> // uint32_t tipini kullanabilmek için şart!

void outb(unsigned short port, unsigned char val);
unsigned char inb(unsigned short port);
void init_graph_mode(void);

/* KRİTİK DÜZELTME: Renk artık 32-bit (uint32_t) kabul ediyor! */
void draw_pixel_pure(int x, int y, uint32_t color);
void clear_screen_gfx(uint32_t color);
void draw_window_pure(int x, int y, int width, int height, uint32_t border_color);

#endif
