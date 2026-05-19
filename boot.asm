section .multiboot
align 4
    MULTIBOOT_MAGIC    equ 0x1BADB002
    MULTIBOOT_FLAGS    equ 0x00000007 ; Grafik modu aktif
    MULTIBOOT_CHECKSUM equ -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

    dd MULTIBOOT_MAGIC
    dd MULTIBOOT_FLAGS
    dd MULTIBOOT_CHECKSUM

    ; GRUB Offset kaymasını önleyen boşluklar (Zorunlu)
    dd 0 ; header_addr
    dd 0 ; load_addr
    dd 0 ; load_end_addr
    dd 0 ; bss_end_addr
    dd 0 ; entry_addr

    ; Grafik Modu Bilgileri (GRUB burayı okuyup ekranı hazırlayacak)
    dd 0    ; mode_type
    dd 1024 ; width
    dd 768  ; height
    dd 32   ; depth

; --- KERNEL.C İÇİN ARKA PLANDA GÜVENLİ YIĞIN (STACK) ALANI AÇIYORUZ ---
section .bss
align 16
stack_bottom:
    resb 16384 ; kernel.c'deki fonksiyonların çökmemesi için 16 KB ram ayırdık
stack_top:

; --- GİRİŞ NOKTASI ---
section .text
global _start
extern kernel_main ; kernel.c içindeki ana fonksiyonun adı (farklıysa burayı düzelt)

_start:
    cli ; 1. Kural: C koduna geçmeden önce tüm donanım kesmelerini kapat

    mov esp, stack_top ; 2. Kural: İşlemciye stack yerini göster (kernel.c artık rahatça çalışabilir)

    ; GRUB'ın bıraktığı multiboot bilgilerini C fonksiyonuna parametre olarak gönderiyoruz
    push ebx ; Multiboot info yapısı
    push eax ; Multiboot magic numarası

    ; kernel.c dosyandaki ana fonksiyona zıpla
    call kernel_main

.hang:
    hlt ; Eğer kernel_main bir şekilde biterse işlemciyi sonsuz uykuya al
    jmp .hang
