#include "controlcenter.h"
#include "ui_controlcenter.h"

ControlCenter::ControlCenter(QWidget *parent): QMainWindow(parent), ui(new Ui::ControlCenter) {
    ui->setupUi(this);

    // Volume initialize
    CoInitialize(nullptr);
}

ControlCenter::~ControlCenter() {
    delete ui;

    // Volume CleanUp
    EndpointVolume->Release();
    DefaultDevice->Release();
    DeviceEnumerator->Release();
    CoUninitialize();
}

int ControlCenter::GetCurrentVolumeValue() {
    CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&DeviceEnumerator);
    DeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &DefaultDevice);
    DefaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, nullptr, (void**)&EndpointVolume);
    EndpointVolume->GetMasterVolumeLevelScalar(&this->VolumeLevel);

    return static_cast<int>(VolumeLevel * 100);
}

int ControlCenter::GetCurrentBrightnessValue() {
    HANDLE hMonitor{ GetMonitorInfo() };
    DWORD minBrightness{};
    DWORD maxBrightness{};
    DWORD CurrentBrightnessValue{};

    GetMonitorBrightness(hMonitor, &minBrightness, &CurrentBrightnessValue, &maxBrightness);

    return CurrentBrightnessValue;
}

HANDLE ControlCenter::GetMonitorInfo() {
    DWORD NumberOfPhysicalMonitors{ 0 };
    PHYSICAL_MONITOR* PhysicalMonitors{ nullptr };

    HMONITOR hMonitor = MonitorFromWindow(GetTopWindow(nullptr), NULL);

    if (!hMonitor || hMonitor == INVALID_HANDLE_VALUE) {
        return INVALID_HANDLE_VALUE;
    }

    if (!GetNumberOfPhysicalMonitorsFromHMONITOR(hMonitor, &NumberOfPhysicalMonitors)) {
        return INVALID_HANDLE_VALUE;
    }

    PhysicalMonitors = static_cast<PHYSICAL_MONITOR*>(malloc(NumberOfPhysicalMonitors * sizeof(PHYSICAL_MONITOR)));

    if (!GetPhysicalMonitorsFromHMONITOR(hMonitor, NumberOfPhysicalMonitors, PhysicalMonitors)) {
        free(PhysicalMonitors);
        return INVALID_HANDLE_VALUE;
    }

    return PhysicalMonitors->hPhysicalMonitor;
}

QString ControlCenter::GetUsername() const { return std::getenv("USERNAME"); }
QString ControlCenter::GetDate() const { return __DATE__; }
QString ControlCenter::GetTime() const { return __TIME__; }

void ControlCenter::GetRunningProcesses() {
    HANDLE hProcessSnap{};
    PROCESSENTRY32 pe32{};
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
    }

    do {
        std::wstring ws(pe32.szExeFile);
        std::string processName(ws.begin(), ws.end());

        runningProcesses.push_back(processName);

    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
}

void ControlCenter::SetUsernameOnLabel() const { ui->Username_Label->setText(this->GetUsername()); }
void ControlCenter::SetDateOnLabel() const { ui->Calendar_Label->setText(this->GetDate()); }
void ControlCenter::SetTimeOnLabel() const { ui->Time_Label->setText(this->GetTime()); }

void ControlCenter::SetVolumeValueOnLabel(int value) { ui->Volume_Value->setText(QString::number(value) + "%");  }
void ControlCenter::SetBrightnessValueOnLabel(int value) { ui->Brightness_Value->setText(QString::number(value) + "%"); }

void ControlCenter::SetNightLight(bool enable) {
    /* Not Compelete */
}

void ControlCenter::on_Dark_Mode_Button_clicked() {
    /* Not Compelete */
}

void ControlCenter::SetTextAndIcons() {
    setWindowTitle("Control Center");
    setWindowIcon(QIcon(IconsPath + "WHI3PER.png"));
    SetUsernameOnLabel();
    SetDateOnLabel();
    SetTimeOnLabel();
    SetVolumeValueOnLabel(this->GetCurrentVolumeValue());
    SetBrightnessValueOnLabel(this->GetCurrentBrightnessValue());
    CheckMuteStatus(this->GetCurrentVolumeValue());

    CheckDarkModeStatus(true);
    CheckNightLightStatus(false);

    ui->Volume_Slider->setValue(this->GetCurrentVolumeValue());
    ui->Brightness_Slider->setValue(this->GetCurrentBrightnessValue());

    /* Labels */
    ui->User_Icon->setPixmap(QPixmap(IconsPath + "User.png"));
    ui->Calendar_Icon->setPixmap(QPixmap(IconsPath + "Calendar.png"));
    ui->Time_Icon->setPixmap(QPixmap(IconsPath + "Time.png"));
    ui->Volume_Icon->setPixmap(QPixmap(IconsPath + "Volume.png"));
    ui->Brightness_Icon->setPixmap(QPixmap(IconsPath + "Brightness.png"));

    /* Buttons */
    ui->Shut_Down_Button->setIcon(QIcon(IconsPath + "Power_Off.png"));
    ui->Restart_Button->setIcon(QIcon(IconsPath + "Restart.png"));
    ui->Sleep_Button->setIcon(QIcon(IconsPath + "Suspend.png"));
    ui->Lock_Button->setIcon(QIcon(IconsPath + "Lock.png"));
    ui->Mute_Button->setIcon(QIcon(IconsPath + "Mute.png"));
    ui->Settings_Button->setIcon(QIcon(IconsPath + "Settings.png"));
    ui->Sign_Out_Button->setIcon(QIcon(IconsPath + "Log_Out.png"));
    ui->Dark_Mode_Button->setIcon(QIcon(IconsPath + "Dark_Mode.png"));
    ui->Night_Light_Button->setIcon(QIcon(IconsPath + "Night_Light.png"));
    ui->Task_Manager_Button->setIcon(QIcon(IconsPath + "Task_Manager"));
    ui->Close_All_Button->setIcon(QIcon(IconsPath + "Close_All"));
    ui->Calculator_Button->setIcon(QIcon(IconsPath + "Calculator.png"));
}

void ControlCenter::StartUp() {
    SetTextAndIcons();
}

void ControlCenter::CheckMuteStatus(int value) {
    if (value == 0)
        ui->Mute_Status_Icon->setPixmap(QPixmap(IconsPath + "True.png"));
    else
        ui->Mute_Status_Icon->setPixmap(QPixmap(IconsPath + "False.png"));
}

void ControlCenter::CheckNightLightStatus(bool flag) {
    if (flag)
        ui->Night_Light_Status_Icon->setPixmap(QPixmap(IconsPath + "True.png"));
    else
        ui->Night_Light_Status_Icon->setPixmap(QPixmap(IconsPath + "False.png"));
}

void ControlCenter::CheckDarkModeStatus(bool flag) {
    if (flag)
        ui->Dark_Style_Status_Icon->setPixmap(QPixmap(IconsPath + "True.png"));
    else
        ui->Dark_Style_Status_Icon->setPixmap(QPixmap(IconsPath + "False.png"));
}

void ControlCenter::CloseProcessByName(const std::wstring& processName) {
    HANDLE hProcessSnap{};
    PROCESSENTRY32 pe32{};
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
    }

    do {
        if (processName == pe32.szExeFile) {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);
            if (hProcess != NULL) {
                TerminateProcess(hProcess, 0);
                CloseHandle(hProcess);
            }
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
}

void ControlCenter::on_Shut_Down_Button_clicked() { std::system("C:\\Windows\\System32\\shutdown /s /f /t 0"); }
void ControlCenter::on_Restart_Button_clicked() { std::system("C:\\Windows\\System32\\shutdown /r /f /t 0"); }
void ControlCenter::on_Sleep_Button_clicked() { /* SetSuspendState(FALSE, TRUE, FALSE); */ }
void ControlCenter::on_Lock_Button_clicked() { LockWorkStation(); }
void ControlCenter::on_Sign_Out_Button_clicked() { ExitWindowsEx(EWX_LOGOFF | EWX_FORCE, SHTDN_REASON_MAJOR_OTHER); }

void ControlCenter::on_Mute_Button_clicked() {
    if (!Mute) {
        Volume = GetCurrentVolumeValue();

        ui->Volume_Value->setText("0%");
        ui->Volume_Slider->setValue(0);
        SetVolumeValueOnLabel(0);
        CheckMuteStatus(0);

        Mute = true;
    }

    else {
        ui->Volume_Value->setText(QString::number(Volume) + "%");
        ui->Volume_Slider->setValue(Volume);
        SetVolumeValueOnLabel(Volume);
        CheckMuteStatus(Volume);

        Mute = false;
    }
}

void ControlCenter::on_Volume_Slider_valueChanged(int value) {
    this->VolumeLevel = static_cast<float>(value) / 100;
    ui->Volume_Value->setText(QString::number(value) + "%");
    EndpointVolume->SetMasterVolumeLevelScalar(VolumeLevel, nullptr);
    SetVolumeValueOnLabel(value);
    CheckMuteStatus(value);
}

void ControlCenter::on_Brightness_Slider_valueChanged(int value) {
    HANDLE hMonitor{ GetMonitorInfo() };
    ui->Brightness_Value->setText(QString::number(value) + "%");
    SetMonitorBrightness(hMonitor, value);
}

void ControlCenter::on_Settings_Button_clicked() {
    LPCWSTR settingsUri{ L"ms-settings:" };
    ShellExecuteW(NULL, L"open", settingsUri, NULL, NULL, SW_SHOWNORMAL);
}

void ControlCenter::on_Night_Light_Button_clicked() { SetNightLight(0); }
void ControlCenter::on_Task_Manager_Button_clicked() { std::system("start taskmgr"); }

void ControlCenter::on_Close_All_Button_clicked() {
    GetRunningProcesses();

    for (auto const& item : runningProcesses)
        if (item == "ControlCenter") {
            auto const iter{ std::remove(runningProcesses.begin(),
                                         runningProcesses.end(),
                                         item) };
            runningProcesses.erase(iter, runningProcesses.end());
        }

    for (const auto& process : runningProcesses) {
        std::wstring wstmp(process.begin(), process.end());
        CloseProcessByName(wstmp);
    }
}

void ControlCenter::on_Calculator_Button_clicked() { std::system("start calc"); }

