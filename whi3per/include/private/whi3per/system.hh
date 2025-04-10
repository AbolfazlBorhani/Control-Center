#pragma once

#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <cstdlib>
#include <string>

namespace System {
	std::string GetUsername();
	std::string GetTime();
	std::string GetDate();

	void ShutDown();
	void Restart();
	void Sleep();

	void TaskManager();
	void Calculator();
	void Settings();

	void LockScreen();
	void SignOut();
	
	void ShowRunnigProcesses();
	void KillProcess();
}
