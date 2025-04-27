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
    const int GREEN{ 10 };
    const int RED{ 12 };
	const int BLUE{ 9 };
    const int YELLOW{ 14 };
    const int WHITE{ 7 };

    auto Print = [](auto Message, auto ColorNumber) {
        SetConsoleTextAttribute(ControlCenter::hConsole, ColorNumber);
        std::cout << Message;
    };

    auto PrintSection = [=](char Case) {
        switch (Case) {
            case '1': Print("[", WHITE); break;
            case '2': Print(" ║ [", WHITE); break;
            case '3': Print("║ ║ [", WHITE); break;
        }

        Print("*", YELLOW);
        Print("] ", WHITE);
    };

    SetConsoleTextAttribute(ControlCenter::hConsole, GREEN);
    Print("                                                                    \n", GREEN);
    Print("    ██████╗ █████╗ ███╗  ██╗████████╗██████╗  █████╗ ██╗            \n", GREEN);
    Print("   ██╔════╝██╔══██╗████╗ ██║╚══██╔══╝██╔══██╗██╔══██╗██║            \n", GREEN);
    Print("   ██║     ██║  ██║██║██╗██║   ██║   ██████╔╝██║  ██║██║            \n", GREEN);
    Print("   ██║     ██║  ██║██║ ████║   ██║   ██╔══██╗██║  ██║██║            \n", GREEN);
    Print("   ╚██████╗╚█████╔╝██║  ███║   ██║   ██║  ██║╚█████╔╝███████╗       \n", GREEN);
    Print("    ╚═════╝ ╚════╝ ╚═╝  ╚══╝   ╚═╝   ╚═╝  ╚═╝ ╚════╝ ╚══════╝       \n", GREEN);
    Print("            ██████╗███████╗███╗  ██╗████████╗███████╗██████╗        \n", GREEN);
    Print("           ██╔════╝██╔════╝████╗ ██║╚══██╔══╝██╔════╝██╔══██╗       \n", GREEN);
    Print("           ██║     █████╗  ██║██╗██║   ██║   █████╗  ██████╔╝       \n", GREEN);
    Print("           ██║     ██╔══╝  ██║ ████║   ██║   ██╔══╝  ██╔══██╗       \n", GREEN);
    Print("           ╚██████╗███████╗██║  ███║   ██║   ███████╗██║  ██║       \n", GREEN);
    Print("            ╚═════╝╚══════╝╚═╝  ╚══╝   ╚═╝   ╚══════╝╚═╝  ╚═╝       \n", GREEN);

    Print("   ╔════════════╗                    ╔════════════╗                 \n", WHITE);
    Print(" ╔═╣  ", WHITE); Print("HardWare  ", YELLOW); 
    Print("╠════════════════╗ ╔═╣ ", WHITE); 
    Print("Brightness ", YELLOW); 
    Print("╠════════════════╗\n", WHITE);
    Print(" ║ ╚════════════╝                ║ ║ ╚════════════╝                ║\n", WHITE);
    PrintSection('2');
    Print("CPUinfo                   ", BLUE); 
    PrintSection('3');
    Print("getcurrentbrightnessvalue ", BLUE); 
    Print("║\n", WHITE);
    PrintSection('2');
    Print("GPUinfo                   ", BLUE);
    PrintSection('3');
    Print("setbrightnessvalue <", BLUE);
    Print("x", YELLOW);
    Print(">    ", BLUE);
    Print("║\n", WHITE);
    PrintSection('2');
    Print("RAMinfo                   ", BLUE);
    Print("║ ╚═══════════════════════════════╝\n", WHITE);
    PrintSection('2');
    Print("DISKinfo                  ", BLUE);
    Print("║   ╔════════════╗                 \n", WHITE);
    PrintSection('2');
    Print("Networkinfo               ", BLUE);
    Print("║ ╔═╣   ", WHITE);
    Print("Volume   ", YELLOW);
    Print("╠════════════════╗\n", WHITE);
    PrintSection('2');
    Print("Undefied                  ", BLUE);
    Print("║ ║ ╚════════════╝                ║\n", WHITE);
    PrintSection('2');
    Print("Undefied                  ", BLUE); 
    PrintSection('3');
    Print("getcurrentvolumevalue     ", BLUE);
    Print("║\n", WHITE);
    PrintSection('2');
    Print("Undefied                  ", BLUE);
    PrintSection('3');
    Print("setvolumevalue            ", BLUE);
    Print("║\n", WHITE);
    PrintSection('2');
    Print("Undefied                  ", BLUE);
    PrintSection('3');
    Print("mute                      ", BLUE);
    Print("║\n", WHITE);
    PrintSection('2');
    Print("Undefied                  ", BLUE);
    PrintSection('3');
    Print("checkmutestatus           ", BLUE);
    Print("║\n", WHITE);
    Print(" ╚═══════════════════════════════╝ ╚═══════════════════════════════╝\n", WHITE);
    Print("   ╔════════════╗                                                   \n", WHITE);
    Print(" ╔═╣   ", WHITE); 
    Print("System   ", YELLOW); 
    Print("╠══════════════════════════════════════════════════╗\n", WHITE);
    Print(" ║ ╚════════════╝                                                  ║\n", WHITE);
    PrintSection('2');
    Print("username                      ", BLUE); 
    PrintSection('1');
    Print("calculator                ", BLUE);
    Print("║\n", WHITE);
    PrintSection('2');
    Print("time                          ", BLUE);
    PrintSection('1');
    Print("settings                  ", BLUE);
    Print("║\n", WHITE);
    PrintSection('2');
    Print("date                          ", BLUE);
    PrintSection('1');
    Print("lockscreen                ", BLUE);
    Print("║\n", WHITE);
    PrintSection('2');
    Print("shutdown                      ", BLUE);
    PrintSection('1');
    Print("signout                   ", BLUE); 
    Print("║\n", WHITE);
    PrintSection('2');
    Print("restart                       ", BLUE);
    PrintSection('1');
    Print("showrunnigprocesses       ", BLUE);
    Print("║\n", WHITE);
    PrintSection('2');
    Print("sleep                         ", BLUE);
    PrintSection('1');
    Print("killprocess <", BLUE);
    Print("x", YELLOW);
    Print(">           ", BLUE);
    Print("║\n", WHITE);
    PrintSection('2');
    Print("taskmanager                   ", BLUE);
    PrintSection('1');
    Print("Undefiend                 ", BLUE);
    Print("║\n", WHITE);
    Print(" ╚═════════════════════════════════════════════════════════════════╝\n", WHITE);
}