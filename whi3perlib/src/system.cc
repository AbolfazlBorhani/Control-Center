#include <whi3perlib/system.hh>

std::string System::GetUsername() {
	return std::getenv("USERNAME");
}

std::string System::GetTime() {
	return __TIME__;
}

std::string System::GetDate() {
	return __DATE__;
}

void System::ShutDown() {
	std::system("C:\\Windows\\System32\\shutdown /s /f /t 0");
}

void System::Restart() {
	std::system("C:\\Windows\\System32\\shutdown /r /f /t 0");	
}

void System::Sleep() {
	/* SetSuspendState(FALSE, TRUE, FALSE); */
}

void System::TaskManager() {
	std::system("start taskmgr");
}

void System::Calculator() {
	std::system("start calc");
}

void System::Settings() {
	LPCWSTR settingsUri{ L"ms-settings:" };
    ShellExecuteW(NULL, L"open", settingsUri, NULL, NULL, SW_SHOWNORMAL);
}

void System::LockScreen() {
	LockWorkStation();
}

void System::SignOut() {
	ExitWindowsEx(EWX_LOGOFF | EWX_FORCE, SHTDN_REASON_MAJOR_OTHER);
}

void System::ShowRunnigProcesses() {
	HANDLE hProcessSnap{};
    PROCESSENTRY32 pe32{};

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Unable to create process snapshot." << std::endl;
        return;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32)) {
        std::cerr << "Error: Unable to retrieve process information." << std::endl;
        CloseHandle(hProcessSnap);
        return;
    }

    std::cout << "List of running processes:" << std::endl;
    do {
    	std::wcout << L"Process Name: " << pe32.szExeFile << std::endl;
        std::wcout << L"Process ID: " << pe32.th32ProcessID << std::endl;
        std::wcout << std::endl;
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
}

void System::KillProcess() {
    DWORD processID{};
    std::cout << "Enter the Process ID to terminate: ";
    std::cin >> processID;
        
    HANDLE hProcess{ OpenProcess(PROCESS_TERMINATE, FALSE, processID) };
    if (hProcess == NULL) {
        std::cerr << "Error: Unable to open process with ID " << processID << std::endl;
        return;
    }

    if (TerminateProcess(hProcess, 0)) {
        std::cout << "Process with ID " << processID << " terminated successfully." << std::endl;
    } else {
        std::cerr << "Error: Unable to terminate process with ID " << processID << std::endl;
    }

    CloseHandle(hProcess);
}