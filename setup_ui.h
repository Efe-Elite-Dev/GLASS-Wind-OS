#ifndef SETUP_UI_H
#define SETUP_UI_H

// 'bool' için gerekli tanımlama
typedef int bool;
#define true 1
#define false 0

typedef struct {
    char username[64];
    int selected_region;
    bool wifi_enabled;
} SetupData;

void draw_setup_screen(int step, SetupData *data);
void handle_mouse_click(int x, int y, int step, SetupData *data);

#endif
