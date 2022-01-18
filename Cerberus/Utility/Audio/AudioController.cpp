#include "AudioController.h"
#include "Utility/AssetManager/AssetManager.h"
IXAudio2* AudioController::audioEngine;
IXAudio2MasteringVoice* AudioController::masterChannel;

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

// Conversion Part Copied and modified from: https://xionghuilin.com/c-convert-between-string-and-cstring-lpwstr/
HANDLE openFile(std::string inputDir)
{
    // Assumes std::string is encoded in the current Windows ANSI codepage
    int bufferlen = ::MultiByteToWideChar(CP_ACP, 0, inputDir.c_str(), (int)inputDir.size(), NULL, 0);

    if (bufferlen == 0)
    {
        // Something went wrong. Perhaps, check GetLastError() and log.
        return 0;
    }

    // Allocate new LPWSTR - must deallocate it later
    LPWSTR convertedString = new WCHAR[bufferlen + 1];

    ::MultiByteToWideChar(CP_ACP, 0, inputDir.c_str(), (int)inputDir.size(), convertedString, bufferlen);

    // Ensure wide string is null terminated
    convertedString[bufferlen] = 0;

    HANDLE fileHandle = CreateFile(convertedString, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);    // Open the file

    free(convertedString);
    return fileHandle;
}

// Loads the specified audio. Do not use \ in path name instead use /'s as \'s break the string.
HRESULT AudioController::LoadAudio(std::string input, bool looping)
{
    if(AssetManager::GetAudio(input) != nullptr)
    {
        Debug::LogError("[AudioController] Tried to load audio with path that already exists! aborting load. Offending Path: %s", input);
        return S_OK;
    }

    std::string fullDir = SOLUTION_DIR + input;
        
    WAVEFORMATEXTENSIBLE waveFormat = { 0 };
    XAUDIO2_BUFFER buffer = { 0 };

    // Convert String.
    HANDLE fileHandle = openFile(fullDir);

    if (fileHandle == INVALID_HANDLE_VALUE)
    {
        Debug::LogHResult(HRESULT_FROM_WIN32(GetLastError()), "Error when opening file from path: %s", input);
        return HRESULT_FROM_WIN32(GetLastError());
    }

    if (SetFilePointer(fileHandle, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
    {
        Debug::LogHResult(HRESULT_FROM_WIN32(GetLastError()), "Error when setting file pointer on file from path: %s", input);
        return HRESULT_FROM_WIN32(GetLastError());
    }

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

    // Add to Asset Manager.
    AssetManager::AddAudio(input, new CAudio(buffer, waveFormat));

    return S_OK;
}

// Plays the specified audio from the AssetManager.
HRESULT AudioController::PlayAudio(std::string path)
{
    if (audioEngine == nullptr)
        AudioController();

    HRESULT hr;

    // Check if the audio exists.
    if (AssetManager::GetAudio(path) == nullptr) {
        Debug::LogHResult(CRYPT_E_NOT_FOUND, "[PlayAudio] Play failed at path: %s", path);
        return CRYPT_E_NOT_FOUND;
    }

    CAudio* audio = AssetManager::GetAudio(path);

    // Create Voice.
    IXAudio2SourceVoice* audioVoice;
    if (FAILED(hr = audioEngine->CreateSourceVoice(&audioVoice, (WAVEFORMATEX*)&audio->format)))
    {
        Debug::LogHResult(hr, "[AudioVoice] Create source voice failed from Path: %s", path);
        return hr;
    }
    if (FAILED(hr = audioVoice->SubmitSourceBuffer(&audio->buffer)))
    {
        Debug::LogHResult(hr, "[AudioVoice] Submit buffer failed from Path: %s", path);
        return hr;
    }
    if (FAILED(hr = audioVoice->Start(0))) 
    {
        Debug::LogHResult(hr, "[AudioVoice] Start failed from Path: %s", path);
        return hr;
    } 

    // Add voice to the audio object so it can be manipulated later.
    audio->voice = audioVoice;
    return S_OK;
}

// Finds the specified audio and stops it emitting.
HRESULT AudioController::StopAudio(std::string path)
{
    // Check if the audio exists.
    if (AssetManager::GetAudio(path) == nullptr) {
        Debug::LogHResult(CRYPT_E_NOT_FOUND, "[StopAudio] Stop failed on audio from path: %s", path);
        return CRYPT_E_NOT_FOUND; 
    }

    CAudio* audio = AssetManager::GetAudio(path);
    if(audio->voice == nullptr)
    {
        Debug::LogError("[StopAudio] Cannot stop audio with path: %s because it does not exist!", path);
        return S_FALSE;
    }
    return audio->voice->Stop();
}
// Destroys the specified audio and removes it from the AssetManager.
HRESULT AudioController::DestroyAudio(std::string path)
{
    // Check if the audio exists.
    if (AssetManager::GetAudio(path) != nullptr) {
        Debug::LogHResult(CRYPT_E_NOT_FOUND, "[DestroyAudio] Stop failed on audio from path: %s", path);
        return CRYPT_E_NOT_FOUND;
    }
    AssetManager::RemoveAudio(path);
    return S_OK;
}