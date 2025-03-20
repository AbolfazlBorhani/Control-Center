#include <whi3perlib/hardware.hh>

void HardWare::CPUInfo() {
    int CPUInfo[4] = {-1};
    char CPUBrandString[0x40] = {0};
    std::vector<std::vector<std::string>> CPUFeatures{};

    __cpuid(CPUInfo, 0x80000000);
    int nExIds = CPUInfo[0];

    __cpuid(CPUInfo, 0x80000002);
    memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
    __cpuid(CPUInfo, 0x80000003);
    memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
    __cpuid(CPUInfo, 0x80000004);
    memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
    std::cout << "CPU Name:\n";
    for (std::size_t i{ 4 }; i < strlen(CPUBrandString); ++i) {
    	std::cout << CPUBrandString[i];
	}
	std::cout << "\n\n";
	
    __cpuid(CPUInfo, 0x80000001);
    if (CPUInfo[3] & (1 << 29)) {
        std::cout << "CPU Architecture:\n    64-bit CPU" << "\n\n";
    } else {
        std::cout << "CPU Architecture:\n    32-bit CPU" << "\n\n";
    }

    SYSTEM_INFO sysInfo{};
    GetSystemInfo(&sysInfo);
    std::cout << "Number of logical cores:\n    " << sysInfo.dwNumberOfProcessors << "\n\n";

    DWORD length{ 0 };
    GetLogicalProcessorInformation(nullptr, &length);
    std::vector<SYSTEM_LOGICAL_PROCESSOR_INFORMATION> buffer(length / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION));
    GetLogicalProcessorInformation(buffer.data(), &length);

    int physicalCores{ 0 };
    for (const auto& info : buffer) {
        if (info.Relationship == RelationProcessorCore) {
            ++physicalCores;
        }
    }
    std::cout << "Number of physical cores:\n    " << physicalCores << "\n\n";

    __cpuid(CPUInfo, 1);
    std::cout << "CPU Features:\n";
    if (CPUInfo[3] & (1 << 23)) {
        std::cout << "    MMX Supported" << std::endl;
    }
    if (CPUInfo[3] & (1 << 25)) {
        std::cout << "    SSE Supported" << std::endl;
    }
    if (CPUInfo[3] & (1 << 26)) {
        std::cout << "    SSE2 Supported" << std::endl;
    }
    if (CPUInfo[2] & (1 << 0)) {
        std::cout << "    SSE3 Supported" << std::endl;
    }
    if (CPUInfo[2] & (1 << 9)) {
        std::cout << "    SSSE3 Supported" << std::endl;
    }
    if (CPUInfo[2] & (1 << 19)) {
        std::cout << "    SSE4.1 Supported" << std::endl;
    }
    if (CPUInfo[2] & (1 << 20)) {
        std::cout << "    SSE4.2 Supported" << std::endl;
    }
    if (CPUInfo[2] & (1 << 28)) {
        std::cout << "    AVX Supported" << std::endl;
    }
}

void HardWare::GPUInfo() {
    HRESULT hr{};

    IDXGIFactory* pFactory{ nullptr };
    hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);
    if (FAILED(hr)) {
        std::cerr << "Failed to create DXGI factory." << std::endl;
        return;
    }

    IDXGIAdapter* pAdapter{ nullptr };
    for (UINT i{ 0 }; pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++i) {
        DXGI_ADAPTER_DESC desc;
        hr = pAdapter->GetDesc(&desc);
        if (FAILED(hr)) {
            std::cerr << "Failed to get adapter description." << std::endl;
            continue;
        }

        std::wcout << L"GPU " << i + 1 << L": " << desc.Description << std::endl;
        std::wcout << L"Vendor ID: " << desc.VendorId << std::endl;
        std::wcout << L"Device ID: " << desc.DeviceId << std::endl;
        std::wcout << L"SubSys ID: " << desc.SubSysId << std::endl;
        std::wcout << L"Revision: " << desc.Revision << std::endl;
        
        std::wcout << L"Dedicated Video Memory: " 
		           << desc.DedicatedVideoMemory / 1024 / 1024 
				   << L" MB" << std::endl;
				   
        std::wcout << L"Shared System Memory: " 
		           << desc.SharedSystemMemory / 1024 / 1024 
				   << L" MB" << std::endl;
		
		std::cout << std::endl;
        pAdapter->Release();
    }

    pFactory->Release();
}

void HardWare::RAMInfo() {
    MEMORYSTATUSEX memInfo{};
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    std::cout << "Total Physical Memory:\n    " 
		      << memInfo.ullTotalPhys / (1024 * 1024) 
			  << " MB" << "\n\n";
    
	std::cout << "Available Physical Memory:\n    " 
			  << memInfo.ullAvailPhys / (1024 * 1024) 
			  << " MB" << "\n\n";
    
	std::cout << "Total Virtual Memory:\n    "      
			  << memInfo.ullTotalVirtual / (1024 * 1024) 
			  << " MB" << "\n\n";
			  
    std::cout << "Available Virtual Memory:\n    "  
			  << memInfo.ullAvailVirtual / (1024 * 1024) 
			  << " MB" << "\n\n";
}

void HardWare::DISKInfo() {
    std::vector<std::string> Drives{};
    char driveLetters[26];
    DWORD DriveMask{ GetLogicalDrives() };

    if (DriveMask == 0) {
        std::cerr << "Failed to get logical drives." << std::endl;
        return;
    }

    for (std::size_t i { 0 }; i < 26; ++i) {
        if (DriveMask & (1 << i)) {
            std::string Drive{ std::string(1, 'A' + i) + ":\\" };
            Drives.push_back(Drive);
        }
    }
    
    ULARGE_INTEGER FreeBytesAvailable, TotalNumberOfBytes, TotalNumberOfFreeBytes;
	
	for (const auto& Drive : Drives) {
	    if (GetDiskFreeSpaceExA(Drive.c_str(), 
                                &FreeBytesAvailable, 
                                &TotalNumberOfBytes, 
                                &TotalNumberOfFreeBytes)) {
	        std::cout << "Drive: " << Drive << std::endl;
	       
            std::cout << "    Total Space: " 
                      << (TotalNumberOfBytes.QuadPart / (1024 * 1024 * 1024)) 
                      << " GB" << std::endl;

	        std::cout << "    Free Space: " 
                      << (TotalNumberOfFreeBytes.QuadPart / (1024 * 1024 * 1024)) 
                      << " GB" << std::endl;

			std::cout << std::endl;
	    } else {
	        std::cerr << "Failed to get disk space for drive " << Drive << std::endl;
	    }
	}
}

void HardWare::NetworkInfo() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return;
    }

    ULONG bufferSize = 0;
    if (GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, NULL, NULL, &bufferSize) == ERROR_BUFFER_OVERFLOW) {
        PIP_ADAPTER_ADDRESSES adapterAddresses = (PIP_ADAPTER_ADDRESSES)malloc(bufferSize);
        if (adapterAddresses == NULL) {
            std::cerr << "Memory allocation failed." << std::endl;
            WSACleanup();
            return;
        }

        if (GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, NULL, adapterAddresses, &bufferSize) == NO_ERROR) {
            PIP_ADAPTER_ADDRESSES adapter = adapterAddresses;
            while (adapter) {
                std::wcout << L"Adapter Name: " << adapter->FriendlyName << std::endl;
                std::wcout << L"    Description: " << adapter->Description << std::endl;

                PIP_ADAPTER_UNICAST_ADDRESS unicastAddress = adapter->FirstUnicastAddress;
                while (unicastAddress) {
                    char ipStr[INET6_ADDRSTRLEN];
                    DWORD ipStrLength = INET6_ADDRSTRLEN;
                    if (WSAAddressToString(unicastAddress->Address.lpSockaddr, unicastAddress->Address.iSockaddrLength, NULL, ipStr, &ipStrLength) == 0) {
                        std::cout << "    IP Address: " << ipStr << std::endl;
                    }
                    unicastAddress = unicastAddress->Next;
                }

                adapter = adapter->Next;
                std::wcout << std::endl;
            }
        } else {
            std::cerr << "GetAdaptersAddresses failed." << std::endl;
        }

        free(adapterAddresses);
    } else {
        std::cerr << "GetAdaptersAddresses failed to get buffer size." << std::endl;
    }

    WSACleanup();
}