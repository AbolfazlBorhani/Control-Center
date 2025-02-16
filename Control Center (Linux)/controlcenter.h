#ifndef CONTROLCENTER_H
#define CONTROLCENTER_H

#define LINUX_REBOOT_CMD_POWER_OFF 0x4321fedc

#include <QMainWindow>
#include <QPixmap>
#include <QIcon>
#include <QString>

#include <sys/reboot.h>
#include <unistd.h>

#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class ControlCenter; }
QT_END_NAMESPACE

class ControlCenter : public QMainWindow {
    Q_OBJECT

public:
    ControlCenter(QWidget *parent = nullptr);
    ~ControlCenter();

    void SetTextAndIcons();

    QString GetDate() const;
    QString GetTime() const;
    QString GetUsername() const;

    void SetDateOnLabel() const;
    void SetTimeOnLabel() const;
    void setUsernameOnLabel() const;

    void SetVolumeValue(int);
    QString GetCurrentVolumeValue();

    void CheckMuteStatus(int);
    void CheckNightLightStatus();
    void CheckDarkStyleStatus();

    void RunProcess();


private slots:
    void on_Volume_Slider_valueChanged(int value);
    void on_Brightness_Slider_valueChanged(int value);

    void on_Lock_Button_clicked();
    void on_Mute_Button_clicked();
    void on_Settings_Button_clicked();
    void on_Power_Off_Button_clicked();
    void on_Restart_Button_clicked();
    void on_Suspend_Button_clicked();
    void on_Log_Out_Button_clicked();
    void on_Dark_Mode_Button_clicked();
    void on_Night_Light_Button_clicked();

private:
    Ui::ControlCenter *ui;

    QString IconsPath{ "/home/whi3per/WHI3PER/Documents/Project's/Control Center/ControlCenter/Icons/" };

    int Volume{};

    bool Mute{};
    bool DarkStyle{};
    bool NightLight{};
};

#endif // CONTROLCENTER_H
