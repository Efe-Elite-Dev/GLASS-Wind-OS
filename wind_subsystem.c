import customtkinter as ctk
from sky_setup_ui import SkyCoreSetup

class SkyKernelCore(ctk.CTk):
    def __init__(self):
        super().__init__()
        
        self.title("Sky Core OS v1.5 [vortex-kernel] - Active")
        self.geometry("1024x768")
        self.resizable(False, False)
        
        self.kernel_frame = ctk.CTkFrame(self, fg_color="#0f0a1c")
        self.kernel_frame.pack(fill="both", expand=True)
        
        self.load_main_os_interface()

    def load_main_os_interface(self):
        status_lbl = ctk.CTkLabel(
            self.kernel_frame, 
            text="🌪️ SKY CORE OS [ vortex-kernel v1.5 ] AKTIF\nSistem başarıyla ana belleğe yüklendi.", 
            font=("Arial", 22, "bold"), 
            text_color="#00d2d3"
        )
        status_lbl.pack(pady=60)
        
        terminal_view = ctk.CTkTextBox(self.kernel_frame, width=850, height=450, fg_color="black", text_color="#1dd1a1", font=("Consolas", 13))
        terminal_view.pack(pady=10)
        terminal_view.insert("0.0", "sky_core@vortex-kernel:~$ core_init --status SUCCESS\nsky_core@vortex-kernel:~$ Sihirbaz tamamlandı, ana döngü serbest bırakıldı.\nsky_core@vortex-kernel:~$ kernel_status: ONLINE\nsky_core@vortex-kernel:~$ ")

def run_main_system():
    main_os = SkyKernelCore()
    main_os.mainloop()

if __name__ == "__main__":
    # Önce sihirbazı çalıştır, kapandığı an kod alt satırdaki run_main_system'a akacak
    wizard = SkyCoreSetup()
    wizard.mainloop()
    
    # Döngü kırıldı, doğrudan çekirdeğe uçur:
    run_main_system()
