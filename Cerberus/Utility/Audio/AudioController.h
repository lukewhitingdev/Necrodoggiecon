#pragma once
#include <Windows.h>
#include <xaudio2.h>
class AudioController
{
public:
	AudioController();
	HRESULT LoadSound(LPCWSTR input);

private:

	IXAudio2* audioEngine;
	IXAudio2MasteringVoice* masterChannel;
};

