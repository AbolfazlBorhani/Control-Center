#include "controlcenter.h"
#include "./ui_controlcenter.h"

ControlCenter::ControlCenter(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::ControlCenter)
{
    ui->setupUi(this);
}

ControlCenter::~ControlCenter()
{
    delete ui;
}

void ControlCenter::SetTextAndIcons() {
    setWindowTitle("Control Center");
    ui->Volume_Value->setText(this->GetCurrentVolumeValue() + "%");
    ui->Volume_Slider->setValue(this->GetCurrentVolumeValue().toInt());

    /* Labels */
    ui->User_Icon->setPixmap(QPixmap(IconsPath + "User.png"));
    ui->Calendar_Icon->setPixmap(QPixmap(IconsPath + "Calendar.png"));
    ui->Time_Icon->setPixmap(QPixmap(IconsPath + "Time.png"));
    ui->Volume_Icon->setPixmap(QPixmap(IconsPath + "Volume.png"));
    ui->Brightness_Icon->setPixmap(QPixmap(IconsPath + "Brightness.png"));

    /* Buttons */
    ui->Power_Off_Button->setIcon(QIcon(IconsPath + "Power_Off.png"));
    ui->Restart_Button->setIcon(QIcon(IconsPath + "Restart.png"));
    ui->Suspend_Button->setIcon(QIcon(IconsPath + "Suspend.png"));
    ui->Lock_Button->setIcon(QIcon(IconsPath + "Lock.png"));
    ui->Mute_Button->setIcon(QIcon(IconsPath + "Mute.png"));
    ui->Settings_Button->setIcon(QIcon(IconsPath + "Settings.png"));
    ui->Log_Out_Button->setIcon(QIcon(IconsPath + "Log_Out.png"));
    ui->Dark_Mode_Button->setIcon(QIcon(IconsPath + "Dark_Mode.png"));
    ui->Night_Light_Button->setIcon(QIcon(IconsPath + "Night_Light.png"));

    CheckMuteStatus(GetCurrentVolumeValue().toInt());
    CheckNightLightStatus();
    CheckDarkStyleStatus();
}

QString ControlCenter::GetDate() const {
    return __DATE__;
}

QString ControlCenter::GetTime() const {
    return __TIME__;
}

QString ControlCenter::GetUsername() const {
    return getlogin();
}

void ControlCenter::SetDateOnLabel() const {
    ui->Calendar_Label->setText(GetDate());
}

void ControlCenter::SetTimeOnLabel() const {
    ui->Time_Label->setText(GetTime());
}

void ControlCenter::setUsernameOnLabel() const {
    ui->Username_Label->setText(GetUsername());
}

void ControlCenter::SetVolumeValue(int value) {
    std::string command{ "amixer set Master " + std::to_string(value) + "%" };
    std::system(command.c_str());
}

QString ControlCenter::GetCurrentVolumeValue() {
    FILE* pipe = popen("amixer get Master", "r");

    if (!pipe)
        return "Unable to open pipe\n";

    char buffer[128]{};
    std::string result{ "" };

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
        result += buffer;

    pclose(pipe);

    size_t pos{ result.find("[") };

    if (pos != std::string::npos) {
        size_t end_pos = result.find("%", pos);
        std::string volume_str{ result.substr(pos + 1, end_pos - pos - 1) };
        return QString::fromStdString(volume_str);
    }

    else
        return "Could not find volume information\n";
}

void ControlCenter::CheckMuteStatus(int value) {
    if (value == 0)
        ui->Mute_Status_Icon->setPixmap(QPixmap(IconsPath + "True.png"));
    else
        ui->Mute_Status_Icon->setPixmap(QPixmap(IconsPath + "False.png"));
}

void ControlCenter::CheckNightLightStatus() {
    std::string command{ "gsettings get org.gnome.settings-daemon.plugins.color night-light-enabled" };
    std::string result{ "" };

    FILE* pipe = popen(command.c_str(), "r");
    if (pipe) {
        char buffer[128];

        while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
            result += buffer;

        pclose(pipe);


        if (result.find("true") != std::string::npos) {
            NightLight = true;
            ui->Night_Light_Status_Icon->setPixmap(QPixmap(IconsPath + "True.png"));
        }

        else {
            NightLight = false;
            ui->Night_Light_Status_Icon->setPixmap(QPixmap(IconsPath + "False.png"));
        }
    }

    else {
        NightLight = false;
        ui->Night_Light_Status_Icon->setPixmap(QPixmap(IconsPath + "Warning.png"));
        return;
    }
}

void ControlCenter::CheckDarkStyleStatus() {
    FILE* pipe = popen("gsettings get org.gnome.desktop.interface gtk-theme", "r");
    if (!pipe) {
        ui->Dark_Style_Status_Icon->setPixmap(QPixmap(IconsPath + "Warning.png"));
        return;
    }

    char buffer[128];
    std::string result{ "" };

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
        result += buffer;

    pclose(pipe);

    if (result.find("dark") != std::string::npos) {
        ui->Dark_Style_Status_Icon->setPixmap(QPixmap(IconsPath + "True.png"));
        DarkStyle = true;
    }

    else {
        ui->Dark_Style_Status_Icon->setPixmap(QPixmap(IconsPath + "False.png"));
        DarkStyle = false;
    }
}

void ControlCenter::RunProcess() {
    SetTextAndIcons();
    SetDateOnLabel();
    SetTimeOnLabel();
    setUsernameOnLabel();
}

/* *************************** Slider *************************** */

void ControlCenter::on_Volume_Slider_valueChanged(int value) {
    ui->Volume_Value->setText(QString::number(value) + "%");
    SetVolumeValue(value);
    CheckMuteStatus(value);
}

void ControlCenter::on_Brightness_Slider_valueChanged(int value) {
    ui->Brightness_Value->setText(QString::number(value) + "%");
}

/* *************************** Button *************************** */

void ControlCenter::on_Lock_Button_clicked() {
    const char* lockCommand{ "xdg-screensaver lock" };
    std::system(lockCommand);
}

void ControlCenter::on_Mute_Button_clicked() {
    if (!Mute) {
        Volume = GetCurrentVolumeValue().toInt();

        ui->Volume_Value->setText("0%");
        ui->Volume_Slider->setValue(0);
        SetVolumeValue(0);
        CheckMuteStatus(0);

        Mute = true;
    }

    else {
        ui->Volume_Value->setText(QString::number(Volume) + "%");
        ui->Volume_Slider->setValue(Volume);
        SetVolumeValue(Volume);
        CheckMuteStatus(Volume);

        Mute = false;
    }
}

void ControlCenter::on_Settings_Button_clicked() {
    if (std::system("gnome-control-center &"));
    else (std::system("systemsettings5 &"));
}

void ControlCenter::on_Power_Off_Button_clicked() {
    std::system("shutdown now");
}

void ControlCenter::on_Restart_Button_clicked() {
    std::system("sudo reboot");
}

void ControlCenter::on_Suspend_Button_clicked() {
    std::system("systemctl suspend");
}

void ControlCenter::on_Log_Out_Button_clicked() {
    std::system("gnome-session-quit --logout --no-prompt");
}

void ControlCenter::on_Dark_Mode_Button_clicked() {

}

void ControlCenter::on_Night_Light_Button_clicked() {
    CheckNightLightStatus();

    if (NightLight) {
        std::system("gsettings set org.gnome.settings-daemon.plugins.color night-light-enabled false");
        CheckNightLightStatus();
        NightLight = false;
    }

    else {
        system("gsettings set org.gnome.settings-daemon.plugins.color night-light-enabled true");
        CheckNightLightStatus();
        NightLight = true;
    }
}
