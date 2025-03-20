#include <whi3perlib/controlcenter.hh>
#include <whi3perlib/brightness.hh>
#include <whi3perlib/hardware.hh>
#include <whi3perlib/volume.hh>
#include <whi3perlib/system.hh>

void ControlCenter::RunProgram(int argc, char** argv) {
    #if defined _WIN32
    std::system("cls");
    #elif defined(__linux__)
    std::system("clear");
    #elif defined (__APPLE__)
    std::system("clear");
    #endif

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
}

void ControlCenter::Help() {
    std::cout << "Usage:\n"
              << "       [--version]\n"
              << "       [--help]\n\n"
              << "Brightness Section:\n"
              << "       [getcurrentbrightnessvalue]\n"
              << "       [setbrightnessvalue x]\n\n"
              << "HardWare Section:\n"
              << "       [CPUinfo]\n"
              << "       [GPUinfo]\n"
              << "       [RAMinfo]\n"
              << "       [DISKinfo]\n"
              << "       [Networkinfo]\n"
              << "       []\n\n"
              << "System Section:\n"
              << "       [username]\n"
              << "       [time]\n"
              << "       [date]\n"
              << "       [shutdown]\n"
              << "       [restart]\n"
              << "       [sleep]\n"
              << "       [taskmanager]\n"
              << "       [calculator]\n"
              << "       [settings]\n"
              << "       [lockscreen]\n"
              << "       [signout]\n"
              << "       [showrunnigprocesses]\n"
              << "       [killprocess]\n\n"
              << "Volume Section:\n"
              << "       [getcurrentvolumevalue]\n"
              << "       [setvolumevalue x]\n"
              << "       [mute]\n"
              << "       [checkmutestatus]\n\n";        
}