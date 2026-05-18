import customtkinter as ctk
import os

class SkyCoreSetup(ctk.CTk):
    def __init__(self, on_complete_callback=None):
        super().__init__()
        
        # VirtualBox prototipine uygun tam 1024x768 çözünürlük
        self.title("Sky Core OS v1.5 - Setup Wizard")
        self.geometry("1024x768")
        self.resizable(False, False)
        
        # Kurulum bitince ana işletim sistemini tetikleyecek köprü fonksiyonu
        self.on_setup_complete = on_complete_callback
        
        # Kurulum adımları takibi (1: Hoş Geldiniz, 2: Ağ/Konum, 3: Giriş, 4: Masaüstü Arayüzü)
        self.current_step = 1
        
        # Ana Konteyner (Sky Core temasına uygun derin gece moru)
        self.main_frame = ctk.CTkFrame(self, fg_color="#1a122c")
        self.main_frame.pack(fill="both", expand=True)
        
        # İlk adımı çizerek başla
        self.show_step()

    def clear_frame(self):
        for widget in self.main_frame.winfo_children():
            widget.destroy()

    def show_step(self):
        self.clear_frame()
        if self.current_step == 1:
            self.render_step_1()
        elif self.current_step == 2:
            self.render_step_2()
        elif self.current_step == 3:
            self.render_step_3()
        elif self.current_step == 4:
            self.render_step_4()

    # --- 1. EKRAN: HOŞ GELDİNİZ KURULUMU ---
    def render_step_1(self):
        title_lbl = ctk.CTkLabel(self.main_frame, text="İLK KURULUM EKRANI - HOŞ GELDİNİZ", font=("Arial", 24, "bold"), text_color="white")
        title_lbl.pack(pady=20)
        
        center_card = ctk.CTkFrame(self.main_frame, fg_color="white", corner_radius=15, width=600, height=400)
        center_card.pack_propagate(False)
        center_card.pack(pady=40)
        
        logo_placeholder = ctk.CTkLabel(center_card, text="🧭 [ SKY CORE OS PUSULA LOGOSU ]", text_color="#1a122c", font=("Arial", 18, "bold"))
        logo_placeholder.pack(pady=40)
        
        msg_lbl = ctk.CTkLabel(center_card, text="İLK KURULUM EKRANI\nSisteme Hoş Geldiniz!", text_color="#1a122c", font=("Arial", 22, "bold"))
        msg_lbl.pack(pady=20)
        
        btn_frame = ctk.CTkFrame(center_card, fg_color="transparent")
        btn_frame.pack(side="bottom", pady=30)
        
        fast_btn = ctk.CTkButton(btn_frame, text="Hızlı Kurulum (Az)", fg_color="#2b3a67", hover_color="#3a4f8c", text_color="white", font=("Arial", 14, "bold"), command=self.next_step)
        fast_btn.pack(side="left", padx=10)
        
        detailed_btn = ctk.CTkButton(btn_frame, text="Detaylı Kurulum (Başka)", fg_color="#2b3a67", hover_color="#3a4f8c", text_color="white", font=("Arial", 14, "bold"), command=self.next_step)
        detailed_btn.pack(side="left", padx=10)

    # --- 2. EKRAN: TEŞEKKÜRLER, WİFİ & KONUM AYARLAMA ---
    def render_step_2(self):
        title_lbl = ctk.CTkLabel(self.main_frame, text="KONUM & SAAT AYARLAMA", font=("Arial", 24, "bold"), text_color="white")
        title_lbl.pack(pady=15)
        
        left_panel = ctk.CTkFrame(self.main_frame, fg_color="#241a3e", width=450, height=550)
        left_panel.pack_propagate(False)
        left_panel.pack(side="left", padx=30, pady=20)
        
        thanks_lbl = ctk.CTkLabel(left_panel, text="SKY CORE OS v1.5'i\nSeçtiğiniz İçin\nTeşekkürler!", font=("Arial", 20, "bold"), text_color="white")
        thanks_lbl.pack(pady=30)
        
        wifi_title = ctk.CTkLabel(left_panel, text="📶 WiFi A BAĞLANA", font=("Arial", 16, "bold"), text_color="white")
        wifi_title.pack(pady=10)
        
        wifi_box = ctk.CTkFrame(left_panel, fg_color="#1a122c", width=380, height=150)
        wifi_box.pack_propagate(False)
        wifi_box.pack(pady=10)
        
        wifi_1 = ctk.CTkLabel(wifi_box, text="📶 Ağ Adı       ● En İyi Güç", font=("Arial", 14), text_color="green")
        wifi_1.pack(pady=15)
        wifi_2 = ctk.CTkLabel(wifi_box, text="📶 Ağ Adı 2     ● Bağlantı Yok", font=("Arial", 14), text_color="gray")
        wifi_2.pack(pady=5)
        
        skip_btn = ctk.CTkButton(left_panel, text="Atla", fg_color="#44356a", width=150, command=self.next_step)
        skip_btn.pack(side="bottom", pady=30)

        right_panel = ctk.CTkFrame(self.main_frame, fg_color="#241a3e", width=450, height=550)
        right_panel.pack_propagate(False)
        right_panel.pack(side="right", padx=30, pady=20)
        
        map_placeholder = ctk.CTkLabel(right_panel, text="🗺️ [ TÜRKİYE HARİTASI ]", fg_color="#362958", width=400, height=220, text_color="white", font=("Arial", 16))
        map_placeholder.pack(pady=20)
        
        loc_lbl = ctk.CTkLabel(right_panel, text="Konum: [Istanbul, Türkiye]", font=("Arial", 16), text_color="white")
        loc_lbl.pack(pady=10)
        
        time_lbl = ctk.CTkLabel(right_panel, text="Bölge Saati: [GMT+03:00]", font=("Arial", 16), text_color="white")
        time_lbl.pack(pady=10)
        
        save_btn = ctk.CTkButton(right_panel, text="Konum ve Saat Ayarlarını Kaydet", fg_color="#2b3a67", font=("Arial", 14, "bold"), width=300, height=40, command=self.next_step)
        save_btn.pack(side="bottom", pady=40)

    # --- 3. EKRAN: GİRİŞ & HAZIRLIK TAMAMLAMA ---
    def render_step_3(self):
        title_lbl = ctk.CTkLabel(self.main_frame, text="GİRİŞ & TAMAMLAMA", font=("Arial", 24, "bold"), text_color="white")
        title_lbl.pack(pady=20)
        
        center_panel = ctk.CTkFrame(self.main_frame, fg_color="#241a3e", width=500, height=500)
        center_panel.pack_propagate(False)
        center_panel.pack(pady=30)
        
        info_lbl = ctk.CTkLabel(center_panel, text="Giriş Bilgilerini Kontrol Edin.", font=("Arial", 18), text_color="white")
        info_lbl.pack(pady=20)
        
        moon_logo = ctk.CTkLabel(center_panel, text="🌙 [ AY/GECE LOGOSU - 33.png ]", font=("Arial", 16), text_color="#a29bfe")
        moon_logo.pack(pady=30)
        
        complete_lbl = ctk.CTkLabel(center_panel, text="Teşekkürler, Kullanıma Hazır!\nMasaüstüne Gitmek İçin\nHAZIR", font=("Arial", 18, "bold"), text_color="white")
        complete_lbl.pack(pady=20)
        
        start_btn = ctk.CTkButton(center_panel, text="BAŞLAT", fg_color="#10ac84", hover_color="#1dd1a1", font=("Arial", 16, "bold"), width=250, height=45, command=self.next_step)
        start_btn.pack(side="bottom", pady=40)

    # --- 4. EKRAN: PROTOTİP MASAÜSTÜ VE ÇEKMECELİ ARAYÜZ ---
    def render_step_4(self):
        self.main_frame.rowconfigure(0, weight=1)
        self.main_frame.rowconfigure(1, weight=0)
        self.main_frame.columnconfigure(0, weight=1)
        
        # Masaüstü Arka Planı
        desktop_area = ctk.CTkFrame(self.main_frame, fg_color="#1e1b29")
        desktop_area.grid(row=0, column=0, sticky="nsew")
        
        # Hava Durumu Widget'ı (Üst Orta)
        weather_widget = ctk.CTkFrame(desktop_area, fg_color="#2d2640", corner_radius=10, width=420, height=100)
        weather_widget.place(relx=0.5, rely=0.15, anchor="center")
        weather_lbl = ctk.CTkLabel(weather_widget, text="🕒 26:03  |  İstanbul, 18°C Çok Bulutlu", font=("Arial", 14, "bold"), text_color="white")
        weather_lbl.place(relx=0.5, rely=0.5, anchor="center")
        
        # Yanlardaki Statik Sabit Uygulamalar
        left_apps = ctk.CTkLabel(desktop_area, text="[ UYGULAMA ALARI ]\n📷 Kamera\n🎨 Galeri\n🎵 Müzik", text_color="gray", font=("Arial", 13), justify="left")
        left_apps.place(x=40, rely=0.4)
        
        right_apps = ctk.CTkLabel(desktop_area, text="[ UYGULAMALAR ]\n💬 Mesajlar\n🖥️ Terminal\n📁 Dosyalar\n🗺️ Haritalar", text_color="gray", font=("Arial", 13), justify="right")
        right_apps.place(relx=0.95, rely=0.4, anchor="ne")

        # --- ORTADAN ÇIKAN UYGULAMA ÇEKMECESİ ---
        self.app_drawer = ctk.CTkFrame(desktop_area, fg_color="#2d2942", border_color="#5f5380", border_width=2, corner_radius=15, width=560, height=390)
        # Şemadaki gibi varsayılan olarak açık geliyor
        self.app_drawer.place(relx=0.5, rely=0.55, anchor="center")
        
        search_bar = ctk.CTkEntry(self.app_drawer, placeholder_text="🔍 Uygulama veya komut ara...", width=480, fg_color="#1e1b29")
        search_bar.pack(pady=15)
        
        apps_frame = ctk.CTkFrame(self.app_drawer, fg_color="transparent")
        apps_frame.pack(fill="both", expand=True, padx=20, pady=10)
        
        # Çekmece içi uygulama listesi
        mock_apps = ["Dosya Yöneticisi", "Takvim", "E-Posta", "Tarayıcı", "Kod Editörü", "Terminal", "Ayarlar", "Mağaza"]
        for i, app_name in enumerate(mock_apps):
            r = i // 4
            c = i % 4
            app_btn = ctk.CTkButton(apps_frame, text=f"📦\n{app_name}", fg_color="#3d3659", hover_color="#4d4470", width=110, height=85, font=("Arial", 11))
            app_btn.grid(row=r, column=c, padx=12, pady=12)

        # --- GÖREV ÇUBUĞU (TASKBAR) ---
        taskbar = ctk.CTkFrame(self.main_frame, fg_color="#14111f", height=60, corner_radius=0)
        taskbar.grid(row=1, column=0, sticky="ew")
        taskbar.grid_propagate(False)
        
        # Sol Kısım Sistem Simgeleri
        sys_logos = ctk.CTkLabel(taskbar, text="🛠️ ⚙️ ℹ️ >_", text_color="white", font=("Arial", 15))
        sys_logos.pack(side="left", padx=25)
        
        # TAM ORTA BUTON: Basınca Çekmeceyi Tetikleyen Logo
        self.center_trigger_btn = ctk.CTkButton(
            taskbar, 
            text="🌀 [ANA LOGO]", 
            fg_color="#3d3659", 
            hover_color="#5f5380",
            width=150, 
            height=40,
            font=("Arial", 12, "bold"),
            command=self.toggle_drawer
        )
        self.center_trigger_btn.pack(relx=0.5, rely=0.5, anchor="center")
        
        # Şemadaki bilgi metni kutusu
        tooltip_lbl = ctk.CTkLabel(taskbar, text="TUŞUNA BASINCA ÇEKMECE ÇIKTI / GİZLENDİ", text_color="#a29bfe", font=("Arial", 10))
        tooltip_lbl.pack(side="right", padx=15)
        
        # Sağ Kısım Saat Tarih ve Sistemi Kapatıp Bitirme Butonu
        finish_setup_btn = ctk.CTkButton(taskbar, text="Sistemi Başlat 🚀", fg_color="#10ac84", width=120, height=35, command=self.finish_setup)
        finish_setup_btn.pack(side="right", padx=10)

    def toggle_drawer(self):
        # Ortadaki logoya basılınca çekmeceyi animasyonsuz güvenli şekilde açıp kapatır
        if self.app_drawer.winfo_viewable():
            self.app_drawer.place_forget()
        else:
            self.app_drawer.place(relx=0.5, rely=0.55, anchor="center")

    def next_step(self):
        if self.current_step < 4:
            self.current_step += 1
            self.show_step()

    def finish_setup(self):
        # Kurulum bitince ana kernel'e geçiş yapar pencereyi kapatır
        if self.on_setup_complete:
            self.on_setup_complete()
        self.destroy()

if __name__ == "__main__":
    app = SkyCoreSetup()
    app.mainloop()
