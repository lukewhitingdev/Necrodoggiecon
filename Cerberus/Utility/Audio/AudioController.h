#pragma once
#include <Windows.h>
#include <map>
#include "Utility/DebugOutput/Debug.h"
#include "CAudio.h"

// Load Wav Audio. -- Copied and modified from MSDN tutorial https://docs.microsoft.com/en-us/windows/win32/xaudio2/how-to--play-a-sound-with-xaudio2
class AudioController
{
public:
	AudioController();
	static HRESULT LoadAudio(LPCWSTR input, const char* audioID, bool looping);
	static HRESULT PlayAudio(const char* audioID);
	static HRESULT StopAudio(const char* audioID);
	static HRESULT DestroyAudio(const char* audioID);

private:
	static IXAudio2* audioEngine;
	static IXAudio2MasteringVoice* masterChannel;
	static std::map<std::string, CAudio*> audios;
};

