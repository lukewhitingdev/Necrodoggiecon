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

// Helper function to find a chunk the RIFF file.
HRESULT FindChunk(HANDLE fileHandle, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{
    HRESULT hr = S_OK;
    if (INVALID_SET_FILE_POINTER == SetFilePointer(fileHandle, 0, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());

    DWORD chunkType;
    DWORD chunkDataSize;
    DWORD RIFFDataSize = 0;
    DWORD fileType;
    DWORD offset = 0;

    while (hr == S_OK)
    {
        DWORD dwRead;
        if (ReadFile(fileHandle, &chunkType, sizeof(DWORD), &dwRead, NULL) == 0)
            hr = HRESULT_FROM_WIN32(GetLastError());

        if (ReadFile(fileHandle, &chunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
            hr = HRESULT_FROM_WIN32(GetLastError());

        switch (chunkType)
        {
        case 'FFIR': // RIFF backwards cuz of little edian.
            RIFFDataSize = chunkDataSize;
            chunkDataSize = 4;
            if (ReadFile(fileHandle, &fileType, sizeof(DWORD), &dwRead, NULL) == 0)
                hr = HRESULT_FROM_WIN32(GetLastError());
            break;

        default:
            if (SetFilePointer(fileHandle, chunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
                return HRESULT_FROM_WIN32(GetLastError());
        }

        offset += sizeof(DWORD) * 2;

        if (chunkType == fourcc)
        {
            dwChunkSize = chunkDataSize;
            dwChunkDataPosition = offset;
            return S_OK;
        }

        offset += chunkDataSize;
    }
    return S_OK;
}

// Helper function to read the chunk after it has been found.
HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset)
{
    DWORD read;
    if (SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
        return HRESULT_FROM_WIN32(GetLastError());

    if (ReadFile(hFile, buffer, buffersize, &read, NULL) == 0)
        return HRESULT_FROM_WIN32(GetLastError());

    return S_OK;
}

HRESULT AudioController::LoadAudio(LPCWSTR input, const char* audioID, bool looping)
{
    WAVEFORMATEXTENSIBLE waveFormat = { 0 };
    XAUDIO2_BUFFER buffer = { 0 };

    HANDLE fileHandle = CreateFile(input,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0, NULL);    // Open the file

    if (fileHandle == INVALID_HANDLE_VALUE)
        return HRESULT_FROM_WIN32(GetLastError());

    if (SetFilePointer(fileHandle, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
        return HRESULT_FROM_WIN32(GetLastError());

    // Read RIFF Chunk
    DWORD chunkSize;
    DWORD chunkPosition;
    FindChunk(fileHandle, 'FFIR', chunkSize, chunkPosition);
    DWORD filetype;
    ReadChunkData(fileHandle, &filetype, sizeof(DWORD), chunkPosition);
    if (filetype != 'EVAW')
        return S_FALSE;

    // Read FMT Chunk
    FindChunk(fileHandle, ' tmf', chunkSize, chunkPosition);
    ReadChunkData(fileHandle, &waveFormat, chunkSize, chunkPosition);

    //Read the DATA Chunk and write its data to the buffer.
    FindChunk(fileHandle, 'atad', chunkSize, chunkPosition);
    BYTE* audioDataBuffer = new BYTE[chunkSize];
    ReadChunkData(fileHandle, audioDataBuffer, chunkSize, chunkPosition);

    // Setup Buffer properties.
    buffer.AudioBytes = chunkSize;  //size of the audio buffer in bytes
    buffer.pAudioData = audioDataBuffer;  //buffer containing audio data
    buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer

    if(looping)
    {
        // Looping
        buffer.LoopBegin = buffer.PlayBegin; // Tell the buffer to loop.
        buffer.PlayBegin = 0; // Tell the buffer to play from the begining.
        buffer.PlayLength = 0; // Tell the buffer to play the whole buffer.
        buffer.LoopCount = XAUDIO2_LOOP_INFINITE; // Tell the buffer to loop indefinitely.
    }

    // Add to map.
    audios.emplace(std::make_pair(audioID, new Audio(audioID, buffer, waveFormat)));

    return S_OK;
}

HRESULT AudioController::PlayAudio(const char* audioID)
{
    HRESULT hr;

    // Check if the audio exists.
    if (audios.find(audioID) == audios.end()) {
        Debug::LogHResult(CRYPT_E_NOT_FOUND, "[PlayAudio] Play failed on ID: %s", audioID);
        return CRYPT_E_NOT_FOUND;
    }

    Audio* audio = audios.at(audioID);

    // Create Voice.
    IXAudio2SourceVoice* audioVoice;
    if (FAILED(hr = audioEngine->CreateSourceVoice(&audioVoice, (WAVEFORMATEX*)&audio->format)))
    {
        Debug::LogHResult(hr, "[AudioVoice] Create source voice failed on ID: %s", audioID);
        return hr;
    }
    if (FAILED(hr = audioVoice->SubmitSourceBuffer(&audio->buffer)))
    {
        Debug::LogHResult(hr, "[AudioVoice] Submit buffer failed on ID: %s", audioID);
        return hr;
    }
    if (FAILED(hr = audioVoice->Start(0))) 
    {
        Debug::LogHResult(hr, "[AudioVoice] Start failed on ID: %s", audioID);
        return hr;
    } 

    // Add voice to the audio object so it can be manipulated later.
    audio->voice = audioVoice;
    return S_OK;
}
// Finds the specified audio and stops it emitting.
HRESULT AudioController::StopAudio(const char* audioID)
{
    // Check if the audio exists.
    if (audios.find(audioID) == audios.end()) {
        Debug::LogHResult(CRYPT_E_NOT_FOUND, "[StopAudio] Stop failed on ID: %s", audioID);
        return CRYPT_E_NOT_FOUND; 
    }
    if(audios[audioID]->voice == nullptr)
    {
        Debug::LogError("[StopAudio] Cannot stop audio with ID: %s because it does not exist!", audioID);
        return S_FALSE;
    }
    return audios[audioID]->voice->Stop();
}

HRESULT AudioController::DestroyAudio(const char* audioID)
{
    // Check if the audio exists.
    if (audios.find(audioID) == audios.end()) {
        Debug::LogHResult(CRYPT_E_NOT_FOUND, "[DestroyAudio] Stop failed on ID: %s", audioID);
        return CRYPT_E_NOT_FOUND;
    }
    audios.erase(audioID);
    return S_OK;
}