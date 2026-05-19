# boot.s - Sky-Core OS Multiboot Header & Entry Point (GNU Assembler Syntax)
.intel_syntax noprefix

# Multiboot Sabitleri
.set MULTIBOOT_ALIGN,     1 << 0
.set MULTIBOOT_MEMINFO,   1 << 1
.set MULTIBOOT_GRAPHICS,  1 << 2  
.set MULTIBOOT_FLAGS,     MULTIBOOT_ALIGN | MULTIBOOT_MEMINFO | MULTIBOOT_GRAPHICS
.set MULTIBOOT_MAGIC,     0x1BADB002
.set MULTIBOOT_CHECKSUM,  -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

# Multiboot Başlığı (GRUB Ayarları)
.section .multiboot
.align 4
    .long MULTIBOOT_MAGIC
    .long MULTIBOOT_FLAGS
    .long MULTIBOOT_CHECKSUM
    
    # DOĞRU ELF DÜZENİ: Dolgu alanları kaldırıldı, grafik istekleri direkt checksum arkasına yazıldı
    .long 0     # mode_type (0 = Linear Graphics Mode)
    .long 800   # Genişlik (Width)
    .long 600   # Yükseklik (Height)
    .long 32    # Renk Derinliği (BPP)

# Giriş Noktası ve Çekirdek Bağlantısı
.section .text
.global _start
.extern kernel_main

_start:
    cli
    mov esp, OFFSET stack_top   
    
    push ebx                    
    push eax                    
    
    call kernel_main            
    
.halt:
    hlt                         
    jmp .halt

# Yığın (Stack) Bellek Alanı
.section .bss
.align 16
stack_bottom:
    .skip 16384                 
stack_top:
