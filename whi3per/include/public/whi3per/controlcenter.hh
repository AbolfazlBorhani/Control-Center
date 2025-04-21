#pragma once

#include <windows.h>
#include <string>

namespace ControlCenter {
	void RunProgram(int, char**);
	void Help();

	inline HANDLE hConsole{ GetStdHandle(STD_OUTPUT_HANDLE) };
}
