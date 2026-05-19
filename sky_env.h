typedef enum {
    MODE_OOBE,      // Kurulum ekranı
    MODE_DESKTOP    // Masaüstü
} SysMode;

typedef struct {
    SysMode current_mode;
    int cursor_x, cursor_y;
} SkySystem;
