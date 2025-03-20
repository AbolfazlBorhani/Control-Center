#pragma once
#pragma comment(lib, "Dxva2.lib")

#include <highlevelmonitorconfigurationapi.h>
#include <physicalmonitorenumerationapi.h>
#include <windows.h>

namespace Brightness {
	int GetCurrentBrightnessValue();
	HANDLE GetMonitorInfo();	
	void SetBrightnessValue(int);
}
