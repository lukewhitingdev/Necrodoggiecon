#pragma once
#include <Windows.h>
#include <xaudio2.h>
class AudioController
{
public:
	AudioController();
	void LoadSound();

private:

	IXAudio2* audioEngine;
	IXAudio2MasteringVoice* masterChannel;

	HRESULT FindChunk(HANDLE fileHandle, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition);
	HRESULT ReadChunkData(HANDLE fileHandle, void* buffer, DWORD bufferSize, DWORD bufferOffset);
};

