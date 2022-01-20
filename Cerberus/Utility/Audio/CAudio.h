#pragma once
#include <xaudio2.h>
class CAudio
{
public:
	CAudio() : buffer(XAUDIO2_BUFFER()), format(WAVEFORMATEXTENSIBLE()), voice(nullptr) {};
	CAudio(XAUDIO2_BUFFER buffer, WAVEFORMATEXTENSIBLE format) : buffer(buffer), format(format), voice(nullptr) {};
	XAUDIO2_BUFFER buffer;
	WAVEFORMATEXTENSIBLE format;
	IXAudio2SourceVoice* voice;
};