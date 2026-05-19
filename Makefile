#include "mouse.h"
#include "io.h"

static int mouse_x = 400, mouse_y = 300;

void init_mouse() {
    outb(0x64, 0xA8); // Mouse'u aktif et
    // Burada gerekli komutları göndererek mouse'u stream moduna alabilirsin
}

void mouse_handler() {
    uint8_t status = inb(0x64);
    if (!(status & 0x01)) return;

    int8_t x_move = (int8_t)inb(0x60);
    int8_t y_move = (int8_t)inb(0x60);

    mouse_x += x_move;
    mouse_y -= y_move; // Ekran koordinatları ters olduğu için çıkarıyoruz

    // Sınırları kontrol et
    if (mouse_x < 0) mouse_x = 0;
    if (mouse_y < 0) mouse_y = 0;

    update_cursor_position(mouse_x, mouse_y);
}
