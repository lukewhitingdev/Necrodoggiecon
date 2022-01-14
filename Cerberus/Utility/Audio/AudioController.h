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
	static HRESULT LoadAudio(std::string input, bool looping);
	static HRESULT PlayAudio(std::string path);
	static HRESULT StopAudio(std::string path);
	static HRESULT DestroyAudio(std::string path);

private:
	static IXAudio2* audioEngine;
	static IXAudio2MasteringVoice* masterChannel;
};

