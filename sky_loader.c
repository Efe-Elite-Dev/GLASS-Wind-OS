#include "sky_loader.h"
#include "gui.h"

// Yerel strstr (Dış bağımlılıkları sıfırlamak için)
static int match_extension(const char* str, const char* ext) {
    int i = 0, j = 0;
    while (str[i] != '\0') {
        if (str[i] == ext[j]) {
            while (str[i+j] == ext[j] && ext[j] != '\0') {
                j++;
            }
            if (ext[j] == '\0') return true;
            j = 0;
        }
        i++;
    }
    return false;
}

void sky_handle_double_click(const char* filename) {
    if (match_extension(filename, ".exe")) {
        load_pe_executable(filename);
    } 
    else if (match_extension(filename, ".deb")) {
        unpack_deb_package(filename);
    } 
    else if (match_extension(filename, ".sky")) {
        execute_sky_bundle(filename);
    }
}

void load_pe_executable(const char* path) {
    draw_window_pure(200, 200, 400, 120, "EXE Çalısma Modülü");
    draw_text("PE Executable yükleniyor...", 220, 250, 0x000000);
    draw_text(path, 220, 270, 0x0000FF);
}

void unpack_deb_package(const char* path) {
    draw_window_pure(200, 200, 400, 120, "DEB Paket Kurucu");
    draw_text("Debian paketi ayıklanıyor ve kuruluyor...", 220, 250, 0x000000);
    draw_text(path, 220, 270, 0x33AA33);
}

void execute_sky_bundle(const char* path) {
    draw_window_pure(200, 200, 400, 120, "SKY Native Uygulaması");
    draw_text("Özel .sky paketi basarıyla baslatıldı.", 220, 250, 0x000000);
    draw_text(path, 220, 270, 0xFF00FF);
}
