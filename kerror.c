#include "globals.h"
#include "gui.h"

void kpanic(const char* message) {
    uint32_t* fb = (uint32_t*)GRAPHICS_FRAMEBUFFER;
    
    if(fb) {
        for(int i = 0; i < 1000; i++) {
            fb[i] = 0xFFFF0000; 
        }
    }
    
    draw_rect(150, 200, 500, 150, 0xAA0000); 
    draw_text("!!! KERNEL PANIC !!!", 280, 230, 0xFFFFFF);
    draw_text(message, 180, 280, 0xFFFFFF);
    
    while(1) {
        __asm__ volatile("hlt");
    }
}
