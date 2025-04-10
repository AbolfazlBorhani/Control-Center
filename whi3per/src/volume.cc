#include <whi3per/volume.hh>

void Volume::VolumeInitialize() {
	CoInitialize(nullptr);
    CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&Volume::DeviceEnumerator);
    Volume::DeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &Volume::DefaultDevice);
    Volume::DefaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, nullptr, (void**)&Volume::EndpointVolume);
    Volume::EndpointVolume->GetMasterVolumeLevelScalar(&Volume::VolumeLevel);
}

void Volume::VolumeUninitialize() {
	Volume::EndpointVolume->Release();
    Volume::DefaultDevice->Release();
    Volume::DeviceEnumerator->Release();
    CoUninitialize();
}

int Volume::GetCurrentVolumeValue() {
	return static_cast<int>(Volume::VolumeLevel * 100);
}

void Volume::SetVolumeValue(int value) {
    value = (value > 100) ? 100 : value;
    value = (value < 0) ? 0 : value;

	Volume::VolumeLevel = static_cast<float>(value) / 100;
    Volume::EndpointVolume->SetMasterVolumeLevelScalar(Volume::VolumeLevel, nullptr);
}

void Volume::Mute() {
	Volume::EndpointVolume->SetMasterVolumeLevelScalar(0.0, nullptr);
}

bool Volume::CheckMuteStatus() {
	return Volume::GetCurrentVolumeValue() == 0 ? true : false;
}
