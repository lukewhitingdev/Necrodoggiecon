#pragma once
#include <Windows.h>
#include <xaudio2.h>
#include <map>
#include "Utility/DebugOutput/Debug.h"
class AudioController
{
public:
	AudioController();
	HRESULT LoadAudio(LPCWSTR input, const char* audioID, bool looping);
	HRESULT PlayAudio(const char* audioID);
	HRESULT StopAudio(const char* audioID);
	HRESULT DestroyAudio(const char* audioID);

private:

	struct Audio
	{
		Audio() : name(""), voice(nullptr) {};
		Audio(const char* name, XAUDIO2_BUFFER buffer, WAVEFORMATEXTENSIBLE format) : name(name), buffer(buffer), format(format), voice(nullptr) {};
		const char* name;
		XAUDIO2_BUFFER buffer;
		WAVEFORMATEXTENSIBLE format;
		IXAudio2SourceVoice* voice;
	};

	IXAudio2* audioEngine;
	IXAudio2MasteringVoice* masterChannel;

	std::map<std::string, Audio*> audios;
};

