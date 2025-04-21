```
  ██████╗ █████╗ ███╗  ██╗████████╗██████╗  █████╗ ██╗
 ██╔════╝██╗  ██╗████╗ ██║   ██╔══╝██╔══██╗██╗  ██╗██║
 ██║     ██║  ██║██╗██╗██║   ██║   ██████╔╝██║  ██║██║
 ██║     ██║  ██║██║ ████║   ██║   ██╔══██╗██║  ██║██║
 ╚██████╗╚█████╔╝██║  ███║   ██║   ██║  ██║╚█████╔╝███████╗
  ╚═════╝ ╚════╝ ╚═╝  ╚══╝   ╚═╝   ╚═╝  ╚═╝ ╚════╝ ╚══════╝
          ██████╗███████╗███╗  ██╗████████╗███████╗██████╗
         ██╔════╝██╔════╝████╗ ██║   ██╔══╝██╔════╝██╔══██╗
         ██║     █████╗  ██╗██╗██║   ██║   █████╗  ██████╔╝
         ██║     ██╔══╝  ██║ ████║   ██║   ██╔══╝  ██╔══██╗
         ╚██████╗███████╗██║  ███║   ██║   ███████╗██║  ██║
          ╚═════╝╚══════╝╚═╝  ╚══╝   ╚═╝   ╚══════╝╚═╝  ╚═╝

   ╔════════════╗                    ╔════════════╗
 ╔═╣  HardWare  ╠════════════════╗ ╔═╣ Brightness ╠════════════════╗
 ║ ╚════════════╝                ║ ║ ╚════════════╝                ║
 ║ [*] CPUinfo                   ║ ║ [*] getcurrentbrightnessvalue ║
 ║ [*] GPUinfo                   ║ ║ [*] setbrightnessvalue <x>    ║
 ║ [*] RAMinfo                   ║ ╚═══════════════════════════════╝
 ║ [*] DISKinfo                  ║   ╔════════════╗
 ║ [*] Networkinfo               ║ ╔═╣   Volume   ╠════════════════╗
 ║ [*] Undefied                  ║ ║ ╚════════════╝                ║
 ║ [*] Undefied                  ║ ║ [*] getcurrentvolumevalue     ║
 ║ [*] Undefied                  ║ ║ [*] setvolumevalue            ║
 ║ [*] Undefied                  ║ ║ [*] mute                      ║
 ║ [*] Undefied                  ║ ║ [*] checkmutestatus           ║
 ╚═══════════════════════════════╝ ╚═══════════════════════════════╝
   ╔════════════╗
 ╔═╣   System   ╠══════════════════════════════════════════════════╗
 ║ ╚════════════╝                                                  ║
 ║ [*] username                            [*] calculator          ║
 ║ [*] time                                [*] settings            ║
 ║ [*] date                                [*] lockscreen          ║
 ║ [*] shutdown                            [*] signout             ║
 ║ [*] restart                             [*] showrunnigprocesses ║
 ║ [*] sleep                               [*] killprocess         ║
 ║ [*] taskmanager                         [*] Undefiend           ║
 ╚═════════════════════════════════════════════════════════════════╝
```

Command Line Control Center (CLCC)
==================================

Overview
================
The Command Line Control Center (CLCC) is a command-line utility designed to provide control and information retrieval for various system functionalities. It is built using C++ and organized using CMake for easy compilation and integration. The utility is divided into several sections, each handling specific system operations such as brightness control, hardware information, system management, and volume control.

Features
================
Brightness Control:
- Get Current Brightness Value: Retrieve the current brightness level.
- Set Brightness Value: Adjust the brightness to a specified level.

Hardware Information:
- CPU Info: Display detailed information about the CPU.
- GPU Info: Display detailed information about the GPU.
- RAM Info: Display detailed information about the RAM.
- Disk Info: Display detailed information about the disk.
- Network Info: Display detailed information about the network.

System Management:
- Username: Display the current username.
- Time: Display the current system time.
- Date: Display the current system date.
- Shutdown: Shutdown the system.
- Restart: Restart the system.
- Sleep: Put the system to sleep.
- Task Manager: Open the task manager.
- Calculator: Open the calculator.
- Settings: Open the system settings.
- Lock Screen: Lock the screen.
- Sign Out: Sign out of the current user session.
- Show Running Processes: Display a list of currently running processes.
- Kill Process: Terminate a specified process.

Volume Control:
- Get Current Volume Value: Retrieve the current volume level.
- Set Volume Value: Adjust the volume to a specified level.
- Mute: Mute the volume.
- Check Mute Status: Check if the volume is currently muted.

Building the Project
====================
To build the project, ensure you have CMake installed on your system. Follow these steps:

1. Clone the repository:
```
   $ git clone https://github.com/AbolfazlBorhani/Control-Center.git
   $ cd Control-Center
```
2. Run CMake to configure the project:
```
   $ cmake -B build
```
3. Build the project:
```
   $ cmake --build build
```
4. Run the executable:
```
   $ ./build/ControlCenter.exe --help
```
