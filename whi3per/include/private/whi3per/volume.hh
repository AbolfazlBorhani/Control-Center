#pragma once

#include <endpointvolume.h>
#include <mmdeviceapi.h>

namespace Volume {
	void VolumeInitialize();
	void VolumeUninitialize();

	int GetCurrentVolumeValue();
	void SetVolumeValue(int);
	void Mute();
	bool CheckMuteStatus();

	inline IMMDeviceEnumerator* DeviceEnumerator{};
	inline IMMDevice* DefaultDevice{};
	inline IAudioEndpointVolume* EndpointVolume{};
	inline float VolumeLevel{};
}
