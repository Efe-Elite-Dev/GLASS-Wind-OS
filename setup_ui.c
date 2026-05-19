#include "setup_ui.h"

// Screen.c içindeki fonksiyonları burada tanıtıyoruz (Extern)
extern void clear_screen();
extern void draw_text(char* text, int x, int y);
extern void draw_rect(int x, int y, int w, int h);
extern void draw_mouse_cursor();

void draw_setup_screen(int step, SetupData *data) {
    clear_screen();

    switch(step) {
        case 0:
            draw_text("Bilgisayariniza bir ad verin", 100, 50);
            draw_rect(100, 100, 300, 40);
            draw_text("Ileri", 420, 100);
            break;
        case 1:
            draw_text("Bu dogru ulke mi?", 100, 50);
            draw_rect(100, 100, 200, 30);
            draw_text("Evet", 320, 100);
            break;
    }
    draw_mouse_cursor();
}
