#include <whi3perlib/brightness.hh>

int Brightness::GetCurrentBrightnessValue() {
	HANDLE hMonitor{ Brightness::GetMonitorInfo() };
    DWORD minBrightness{};
	DWORD maxBrightness{};
	DWORD CurrentBrightnessValue{};
    GetMonitorBrightness(hMonitor, &minBrightness, &CurrentBrightnessValue, &maxBrightness);

    return CurrentBrightnessValue;
}

HANDLE Brightness::GetMonitorInfo() {
	DWORD NumberOfPhysicalMonitors{ 0 };
    PHYSICAL_MONITOR* PhysicalMonitors{ nullptr };

    HMONITOR hMonitor = MonitorFromWindow(GetTopWindow(nullptr), MONITOR_DEFAULTTOPRIMARY);

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

void Brightness::SetBrightnessValue(int value) {
    value = (value > 100) ? 100 : value;
    value = (value < 0) ? 0 : value;

	HANDLE hMonitor{ Brightness::GetMonitorInfo() };
    SetMonitorBrightness(hMonitor, value);
}
