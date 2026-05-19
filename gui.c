#include "gui.h"

// globals.h içindeki harici değişkenlerin buradaki tanımları
SystemState current_state = STATE_WELCOME;
SetupData os_setup_data;
bool ai_hud_visible = false;

void init_vga() {
    // Grafik belleği başlatma simülasyonu
}

void clear_screen(uint32_t color) {
    uint32_t* fb = (uint32_t*)GRAPHICS_FRAMEBUFFER;
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        fb[i] = color;
    }
}

void draw_pixel(int x, int y, uint32_t color) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        uint32_t* framebuffer = (uint32_t*)GRAPHICS_FRAMEBUFFER;
        framebuffer[y * SCREEN_WIDTH + x] = color;
    }
}

void draw_rect(int x, int y, int w, int h, uint32_t color) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            draw_pixel(x + j, y + i, color);
        }
    }
}

void draw_text(const char* text, int x, int y, uint32_t color) {
    while (*text) {
        draw_rect(x, y, 8, 12, color); 
        x += 10;
        text++;
    }
}

void draw_window_pure(int x, int y, int w, int h, const char* title) {
    draw_rect(x, y, w, h, 0xEEEEEE);
    draw_rect(x, y, w, 30, 0x1A0933);
    draw_text(title, x + 10, y + 8, 0xFFFFFF);
}

void draw_button(const char* label, int x, int y, int w, int h, bool focused) {
    uint32_t btn_color = focused ? 0x4A154B : 0x333333;
    draw_rect(x, y, w, h, btn_color);
    draw_text(label, x + 15, y + (h/2) - 6, 0xFFFFFF);
}

void draw_setup_welcome() {
    clear_screen(0x13011C);
    draw_window_pure(150, 100, 500, 400, "ILK KURULUM EKRANI - HOS GELDINIZ");
    draw_text("ILK KURULUM EKRANI", 280, 160, 0x000000);
    draw_text("Sisteme Hos Geldiniz!", 290, 200, 0x000000);
    draw_button("Hizli Kurulum (Az)", 200, 320, 180, 40, true);
    draw_button("Detayli Kurulum (Baska)", 420, 320, 200, 40, false);
}

void draw_setup_location() {
    clear_screen(0x13011C);
    draw_window_pure(100, 80, 600, 450, "KONUM & SAAT AYARLAMA");
    draw_text("SKY CORE OS v1.5'i Sectiginiz Icin Tesekkurler!", 120, 130, 0x000000);
    draw_rect(340, 160, 230, 120, 0x555555); 
    draw_text("HARITA (TURKIYE)", 390, 210, 0xFFFFFF);
    draw_rect(380, 180, 6, 6, 0xFF0000); 
    draw_text("Konum: [Istanbul, Turkiye]", 340, 300, 0x000000);
    draw_text("Bolge Saati: [GMT+03:00]", 340, 340, 0x000000);
    draw_button("Konum ve Saat Ayarlarini Kaydet", 340, 390, 240, 40, true);
}

void draw_setup_completing() {
    clear_screen(0x13011C);
    draw_window_pure(100, 80, 600, 450, "GIRIS & TAMAMLAMA");
    draw_rect(120, 140, 200, 100, 0x444444);
    draw_text("Konum: [Istanbul]", 130, 260, 0x000000);
    draw_text("Tesekkurler, Kullanima Hazir!", 350, 160, 0x000000);
    draw_text("Masaustune Gitmek Icin HAZIR", 350, 200, 0x000000);
    draw_button("BASLAT", 380, 320, 150, 45, true);
}

void draw_main_desktop() {
    clear_screen(0x1D2A44); 
    draw_rect(520, 20, 260, 120, 0x22FFFFFF); 
    draw_text("26:03", 540, 40, 0xFFFFFF);
    draw_text("Hava Durumu ve Saat", 540, 80, 0xBBBBBB);
    draw_rect(650, 160, 130, 400, 0x33000000);
    draw_text("UYGULAMALAR", 660, 180, 0xFFFFFF);
    draw_button("Terminal", 660, 220, 110, 30, false);
    draw_button("Dosyalar", 660, 260, 110, 30, false);
    draw_button("Mesajlar", 660, 300, 110, 30, false);
    draw_button("Ayarlar", 660, 340, 110, 30, false);
    draw_window_pure(250, 200, 300, 150, "HOS GELDINIZ");
    draw_text("Sisteme Hos Geldiniz!", 270, 250, 0x000000);
    draw_text("GHHOD GERLDIN!", 270, 280, 0xFF0000); 
    draw_rect(0, 560, SCREEN_WIDTH, 40, 0x0F0F1A);
    draw_text("TUSUMUNA BASINCA CEKMECE ACILSIN", 20, 575, 0xFFFFFF);
}

void draw_ai_subsystem_hud() {
    if (!ai_hud_visible) return;
    draw_rect(100, 0, 600, 220, 0xFA050510);
    draw_rect(100, 215, 600, 5, 0xFF00FF); 
    draw_text("--- SKY-NET AI CORE SUBSYSTEM v1.0 ---", 120, 20, 0x00FFFF);
    draw_text("Sorunuzu Yazin: [                                    ]", 120, 70, 0xFFFFFF);
    draw_text("AI Yanıtı: Sistem mimarisi optimize edildi. Komut bekleniyor...", 120, 130, 0x00FF00);
    draw_text("Kapatmak için tekrar 'ALT + SPACE' tuşuna basın.", 120, 180, 0x888888);
}
