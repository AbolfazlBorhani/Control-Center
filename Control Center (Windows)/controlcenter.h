#ifndef CONTROLCENTER_H
#define CONTROLCENTER_H

#include <QMainWindow>
#include <QPushButton>
#include <QVector>
#include <QString>
#include <QPixmap>
#include <QLabel>

#include <physicalmonitorenumerationapi.h>
#include <highlevelmonitorconfigurationapi.h>

#include <endpointvolume.h>
#include <mmdeviceapi.h>
#include <tlhelp32.h>
#include <windows.h>
#include <comdef.h>
#include <tchar.h>

#pragma comment(lib, "Dxva2.lib")

QT_BEGIN_NAMESPACE
namespace Ui { class ControlCenter; }
QT_END_NAMESPACE

class ControlCenter : public QMainWindow {
    Q_OBJECT

public:
    ControlCenter(QWidget *parent = nullptr);
    ~ControlCenter();

    int GetCurrentVolumeValue();
    int GetCurrentBrightnessValue();
    HANDLE GetMonitorInfo();
    QString GetUsername() const;
    QString GetDate() const;
    QString GetTime() const;
    void GetRunningProcesses();

    void SetUsernameOnLabel() const;
    void SetDateOnLabel() const;
    void SetTimeOnLabel() const;
    void SetVolumeValueOnLabel(int);
    void SetBrightnessValueOnLabel(int);
    void SetNightLight(bool);
    void SetTextAndIcons();

    void CheckMuteStatus(int);
    void CheckNightLightStatus(bool);
    void CheckDarkModeStatus(bool);

    void CloseProcessByName(const std::wstring&);
    void StartUp();

private slots:
    void on_Volume_Slider_valueChanged(int value);
    void on_Brightness_Slider_valueChanged(int value);

    void on_Shut_Down_Button_clicked();
    void on_Restart_Button_clicked();
    void on_Sleep_Button_clicked();
    void on_Mute_Button_clicked();
    void on_Settings_Button_clicked();
    void on_Lock_Button_clicked();
    void on_Sign_Out_Button_clicked();
    void on_Night_Light_Button_clicked();
    void on_Dark_Mode_Button_clicked();
    void on_Task_Manager_Button_clicked();
    void on_Close_All_Button_clicked();
    void on_Calculator_Button_clicked();

private:
    Ui::ControlCenter *ui;

    QString IconsPath{ "C:/Users/abolf/OneDrive/Desktop/Icons/" };
    QVector<std::string> runningProcesses{};

    // Volume
    IMMDeviceEnumerator* DeviceEnumerator{ nullptr };
    IMMDevice* DefaultDevice{ nullptr };
    IAudioEndpointVolume* EndpointVolume{ nullptr };

    float VolumeLevel{ 0.0f };
    int VolumePercent{ 0 };
    int Volume{};

    bool Mute{};
    bool DarkStyle{};
    bool NightLight{};

};
#endif // CONTROLCENTER_H
