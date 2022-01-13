#pragma once
#include <Windows.h>
#include <xaudio2.h>
#include <map>
#include "Utility/DebugOutput/Debug.h"

// Load Wav Audio. -- Copied and modified from MSDN tutorial https://docs.microsoft.com/en-us/windows/win32/xaudio2/how-to--play-a-sound-with-xaudio2
class AudioController
{
private:
	struct Audio
	{
		Audio() : name(""), buffer(XAUDIO2_BUFFER()), format(WAVEFORMATEXTENSIBLE()), voice(nullptr) {};
		Audio(const char* name, XAUDIO2_BUFFER buffer, WAVEFORMATEXTENSIBLE format) : name(name), buffer(buffer), format(format), voice(nullptr) {};
		const char* name;
		XAUDIO2_BUFFER buffer;
		WAVEFORMATEXTENSIBLE format;
		IXAudio2SourceVoice* voice;
	};

public:
	AudioController();
	static HRESULT LoadAudio(LPCWSTR input, const char* audioID, bool looping);
	static HRESULT PlayAudio(const char* audioID);
	static HRESULT StopAudio(const char* audioID);
	static HRESULT DestroyAudio(const char* audioID);

private:
	static IXAudio2* audioEngine;
	static IXAudio2MasteringVoice* masterChannel;
	static std::map<std::string, Audio*> audios;
};

