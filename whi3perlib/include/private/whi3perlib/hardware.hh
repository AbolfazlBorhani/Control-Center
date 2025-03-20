#pragma once

// Ethernet | Network
#include <winsock2.h>
#include <windows.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

// CPU
#include <intrin.h>

// GPU
#include <comdef.h>
#include <dxgi.h>
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

#include <iostream>
#include <cstring>
#include <vector>
#include <string>

namespace HardWare {
    void CPUInfo();
	void GPUInfo();
	void RAMInfo();
	void DISKInfo();
    void NetworkInfo();
}

