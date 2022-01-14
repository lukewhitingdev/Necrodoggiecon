#pragma once
#include <xaudio2.h>
class CAudio
{
public:
	CAudio() : name(""), buffer(XAUDIO2_BUFFER()), format(WAVEFORMATEXTENSIBLE()), voice(nullptr) {};
	CAudio(const char* name, XAUDIO2_BUFFER buffer, WAVEFORMATEXTENSIBLE format) : name(name), buffer(buffer), format(format), voice(nullptr) {};
	const char* name;
	XAUDIO2_BUFFER buffer;
	WAVEFORMATEXTENSIBLE format;
	IXAudio2SourceVoice* voice;
};