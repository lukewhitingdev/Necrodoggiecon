#include "AudioController.h"


AudioController::AudioController()
{
	// Initialize COM.
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
		throw;

	// Setup Audio Engine.
	if (FAILED(XAudio2Create(&audioEngine, 0, XAUDIO2_DEFAULT_PROCESSOR)))
		throw;

	// Setup Master Channel / Voice.
	if (FAILED(audioEngine->CreateMasteringVoice(&masterChannel)))
		throw;
}

void AudioController::LoadSound()
{
	WAVEFORMATEXTENSIBLE waveFormat = { 0 };
	XAUDIO2_BUFFER buffer = { 0 };

	// Open the file.
	HANDLE fileHandle = CreateFile(TEXT("D:/Windows/Download/testSound.wav"), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if(fileHandle == INVALID_HANDLE_VALUE)
		throw;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(fileHandle, 0, NULL, FILE_BEGIN))
		throw;

	DWORD chunkSize;
	DWORD chunkPosition;
	DWORD fileType;

	// RIFF Section.
	if(FAILED(FindChunk(fileHandle, 'FIRR', chunkSize, chunkPosition)))
		throw;
	if (FAILED(ReadChunkData(fileHandle, &fileType, sizeof(DWORD), chunkPosition)))
		throw;
	if (fileType != 'FIRR')
		throw;

	// Format Section.
	if (FAILED(FindChunk(fileHandle, 'fmt', chunkSize, chunkPosition)))
		throw;
	if (FAILED(ReadChunkData(fileHandle, &waveFormat, sizeof(DWORD), chunkPosition)))
		throw;

	// Data Section.
	FindChunk(fileHandle, 'atad', chunkSize, chunkSize);
	BYTE* pDataBuffer = new BYTE[chunkSize];
	ReadChunkData(fileHandle, pDataBuffer, chunkSize, chunkSize);

	// Populate Buffer
	buffer.AudioBytes = chunkSize;  //size of the audio buffer in bytes
	buffer.pAudioData = pDataBuffer;  //buffer containing audio data
	buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer

	// Play Sound. Maybe Re-Factor Afterwards.

	IXAudio2SourceVoice* sourceChannel;
	if (FAILED(audioEngine->CreateSourceVoice(&sourceChannel, (WAVEFORMATEX*)&waveFormat)))
		throw;

	if (FAILED(sourceChannel->SubmitSourceBuffer(&buffer)))
		throw;

	if (FAILED(sourceChannel->Start(0)))
		throw;
}
