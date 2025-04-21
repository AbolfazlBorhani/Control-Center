#include <whi3per/controlcenter.hh>
#include <whi3per/brightness.hh>
#include <whi3per/hardware.hh>
#include <whi3per/volume.hh>
#include <whi3per/system.hh>

void ControlCenter::RunProgram(int argc, char** argv) {
    std::system("chcp 65001");
    std::system("cls");

    if (argc < 2) {
        ControlCenter::Help();
    }

    else {
        std::string command{ argv[1] };

        if (command == "--version") {
            std::cout << "Control Center (Win): v1.0.0" << std::endl;
        }

        else if (command == "--help") {
            ControlCenter::Help();
        }

        /* ***************************************************************************************************** */

        else if (command == "getcurrentbrightnessvalue") {
            std::cout << "Brightness value: " << Brightness::GetCurrentBrightnessValue() << std::endl;
        }

        else if (command == "setbrightnessvalue") {
            Brightness::SetBrightnessValue(std::atoi(argv[2]));
        }

        /* ***************************************************************************************************** */

        else if (command == "CPUinfo") {
            HardWare::CPUInfo();
        }

        else if (command == "GPUinfo") {
            HardWare::GPUInfo();
        }

        else if (command == "RAMinfo") {
            HardWare::RAMInfo();
        }

        else if (command == "DISKinfo") {
            HardWare::DISKInfo();
        }

        else if (command == "Networkinfo") {
            HardWare::NetworkInfo();
        }

        /* ***************************************************************************************************** */

        else if (command == "username") {
            std::cout << "Username: " << System::GetUsername() << std::endl;
        }

        else if (command == "time") {
            std::cout << "Time: " << System::GetTime() << std::endl;
        }

        else if (command == "date") {
            std::cout << "Date: " << System::GetDate() << std::endl;
        }

        else if (command == "shutdown") {
            System::ShutDown();
        }

        else if (command == "restart") {
            System::Restart();
        }

        else if (command == "sleep") {
            System::Sleep();
        }

        else if (command == "taskmanager") {
            System::TaskManager();
        }

        else if (command == "calculator") {
            System::Calculator();
        }

        else if (command == "settings") {
            System::Settings();
        }

        else if (command == "lockscreen") {
            System::LockScreen();
        }

        else if (command == "signout") {
            System::SignOut();
        }

        else if (command == "showrunnigprocesses") {
            System::ShowRunnigProcesses();
        }

        else if (command == "killprocess") {
            System::KillProcess();
        }

        /* ***************************************************************************************************** */

        else if (command == "getcurrentvolumevalue") {
            Volume::VolumeInitialize();
            std::cout << "Volume value: " << Volume::GetCurrentVolumeValue() << std::endl;
            Volume::VolumeUninitialize();
        }

        else if (command == "setvolumevalue") {
            Volume::VolumeInitialize();
            Volume::SetVolumeValue(std::atoi(argv[2]));
            Volume::VolumeUninitialize();
        }

        else if (command == "mute") {
            Volume::VolumeInitialize();
            Volume::Mute();
            Volume::VolumeUninitialize();
        }

        else if (command == "checkmutestatus") {
            Volume::VolumeInitialize();
            std::cout << std::boolalpha;
            std::cout << "Mute status: " << Volume::CheckMuteStatus() << std::endl;
            Volume::VolumeUninitialize();
        }
    }

    std::system("pause>0");
    std::system("cls");
}

void ControlCenter::Help() {
    const int ONE{ 10 };
    const int TWO{ 12 };
	const int THREE{ 9 };
    const int FOUR{ 14 };

    SetConsoleTextAttribute(ControlCenter::hConsole, ONE);
    std::cout << "                                                                    \n";
    std::cout << "  ██████╗ █████╗ ███╗  ██╗████████╗██████╗  █████╗ ██╗              \n";
    std::cout << " ██╔════╝██╗  ██╗████╗ ██║   ██╔══╝██╔══██╗██╗  ██╗██║              \n";
    std::cout << " ██║     ██║  ██║██╗██╗██║   ██║   ██████╔╝██║  ██║██║              \n";
    std::cout << " ██║     ██║  ██║██║ ████║   ██║   ██╔══██╗██║  ██║██║              \n"; 
    std::cout << " ╚██████╗╚█████╔╝██║  ███║   ██║   ██║  ██║╚█████╔╝███████╗         \n";
    std::cout << "  ╚═════╝ ╚════╝ ╚═╝  ╚══╝   ╚═╝   ╚═╝  ╚═╝ ╚════╝ ╚══════╝         \n";
    std::cout << "          ██████╗███████╗███╗  ██╗████████╗███████╗██████╗          \n";
    std::cout << "         ██╔════╝██╔════╝████╗ ██║   ██╔══╝██╔════╝██╔══██╗         \n";
    std::cout << "         ██║     █████╗  ██╗██╗██║   ██║   █████╗  ██████╔╝         \n";
    std::cout << "         ██║     ██╔══╝  ██║ ████║   ██║   ██╔══╝  ██╔══██╗         \n";
    std::cout << "         ╚██████╗███████╗██║  ███║   ██║   ███████╗██║  ██║         \n";
    std::cout << "          ╚═════╝╚══════╝╚═╝  ╚══╝   ╚═╝   ╚══════╝╚═╝  ╚═╝         \n";
    SetConsoleTextAttribute(ControlCenter::hConsole, TWO);
    std::cout << "   ╔════════════╗                    ╔════════════╗                 \n";
    SetConsoleTextAttribute(ControlCenter::hConsole, THREE);
    std::cout << " ╔═╣  HardWare  ╠════════════════╗ ╔═╣ Brightness ╠════════════════╗\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, FOUR);
    std::cout << " ║ ╚════════════╝                ║ ║ ╚════════════╝                ║\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, TWO);
    std::cout << " ║ [*] CPUinfo                   ║ ║ [*] getcurrentbrightnessvalue ║\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, THREE);
    std::cout << " ║ [*] GPUinfo                   ║ ║ [*] setbrightnessvalue <x>    ║\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, FOUR);
    std::cout << " ║ [*] RAMinfo                   ║ ╚═══════════════════════════════╝\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, TWO);
    std::cout << " ║ [*] DISKinfo                  ║   ╔════════════╗                 \n";
    SetConsoleTextAttribute(ControlCenter::hConsole, THREE);
    std::cout << " ║ [*] Networkinfo               ║ ╔═╣   Volume   ╠════════════════╗\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, FOUR);
    std::cout << " ║ [*] Undefied                  ║ ║ ╚════════════╝                ║\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, TWO);
    std::cout << " ║ [*] Undefied                  ║ ║ [*] getcurrentvolumevalue     ║\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, THREE);
    std::cout << " ║ [*] Undefied                  ║ ║ [*] setvolumevalue            ║\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, FOUR);
    std::cout << " ║ [*] Undefied                  ║ ║ [*] mute                      ║\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, TWO);
    std::cout << " ║ [*] Undefied                  ║ ║ [*] checkmutestatus           ║\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, THREE);
    std::cout << " ╚═══════════════════════════════╝ ╚═══════════════════════════════╝\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, FOUR);
    std::cout << "   ╔════════════╗                                                   \n";
    SetConsoleTextAttribute(ControlCenter::hConsole, TWO);
    std::cout << " ╔═╣   System   ╠══════════════════════════════════════════════════╗\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, THREE);
    std::cout << " ║ ╚════════════╝                                                  ║\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, FOUR);
    std::cout << " ║ [*] username                      [*] calculator                ║\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, TWO);
    std::cout << " ║ [*] time                          [*] settings                  ║\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, THREE);
    std::cout << " ║ [*] date                          [*] lockscreen                ║\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, FOUR);
    std::cout << " ║ [*] shutdown                      [*] signout                   ║\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, TWO);
    std::cout << " ║ [*] restart                       [*] showrunnigprocesses       ║\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, THREE);
    std::cout << " ║ [*] sleep                         [*] killprocess <x>           ║\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, FOUR);
    std::cout << " ║ [*] taskmanager                   [*] Undefiend                 ║\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, TWO);
    std::cout << " ╚═════════════════════════════════════════════════════════════════╝\n";
    SetConsoleTextAttribute(ControlCenter::hConsole, 7);    
}
