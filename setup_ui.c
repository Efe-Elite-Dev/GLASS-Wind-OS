#include "setup_ui.h"
#include "screen.h" // Kendi ekran kütüphanen

void draw_setup_screen(int step, SetupData *data) {
    clear_screen(); // Ekranı temizle

    switch(step) {
        case 0: // İsim Giriş Ekranı
            draw_text("Bilgisayariniza bir ad verin", 100, 50);
            draw_rect(100, 100, 300, 40); // İsim kutusu
            draw_text("Ileri", 420, 100);   // İleri butonu
            break;
            
        case 1: // Bölge Seçimi
            draw_text("Bu dogru ulke/bolge mi?", 100, 50);
            draw_rect(100, 100, 200, 30); // "Türkiye" kutusu
            draw_text("Evet", 320, 100);
            break;
            
        // Diğer ekranlar buraya eklenecek...
    }
    
    // Mouse imlecini her zaman en son çiz
    draw_mouse_cursor(); 
}
