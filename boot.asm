section .multiboot
align 4
    MAGIC    equ 0x1BADB002
    FLAGS    equ 0x00000007 ; Bit 0 (Hizala) + Bit 1 (Bellek Bilgisi) + Bit 2 (Grafik Modu İsteği)
    CHECKSUM equ -(MAGIC + FLAGS)

    dd MAGIC
    dd FLAGS
    dd CHECKSUM
    
    ; Multiboot Grafik Alanı (Görseldeki arayüz için VBE Grafik Modu)
    dd 0          ; mode_type (0 = Lineer Grafik Modu)
    dd 1024       ; Genişlik (Width)
    dd 768        ; Yükseklik (Height)
    dd 32         ; Renk Derinliği (BPP - Bits Per Pixel)

section .bss
align 16
stack_bottom:
    resb 16384    ; 16 KB Kernel Yığın Alanı
stack_top:

section .text
global _start
extern kernel_main

_start:
    cli                ; Donanım kesmelerini kapat
    mov esp, stack_top ; Stack pointer'ı ayarla

    push ebx           ; Multiboot bilgi yapısının adresini stack'e at (Claude'un ekran adresini bulması için)
    call kernel_main   ; Claude'un yazacağı kernel_main(multiboot_info_t* mbi) fonksiyonunu çağır

.hang:
    hlt
    jmp .hang
