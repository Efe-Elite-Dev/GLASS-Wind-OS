void kernel_main(void) {
    // VGA Metin Modu (Text Mode) belleği 0xB8000 adresinden başlar.
    // Her karakter 2 byte'tır: 1 byte harf için, 1 byte renk için.
    volatile unsigned short* vga_buffer = (unsigned short*)0xB8000;
    
    // 1. Ekranı temizle (Her yeri boşluk karakteri ve gri renk yap)
    for(int i = 0; i < 80 * 25; i++) {
        vga_buffer[i] = (unsigned short)(' ' | (0x07 << 8));
    }

    // 2. Ekrana yazacağımız mesaj
    const char* str = "Wind OS Saf Kernel Basariyla Baslatildi!";
    
    // 3. Mesajı ekrana bas (0x0F = Siyah arkaplan, Parlak beyaz yazı)
    int index = 0;
    while(str[index] != '\0') {
        vga_buffer[index] = (unsigned short)(str[index] | (0x0F << 8));
        index++;
    }
    
    // 4. Kernel kapanmasın diye sonsuz döngü
    while(1) {
        // Sistem burada güvenle bekleyecek
    }
}
