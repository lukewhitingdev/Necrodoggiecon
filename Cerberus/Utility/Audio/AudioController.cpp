#include "AudioController.h"
FMOD::System* AudioController::FMODSystem;

void AudioController::Initialize()
{
	if (FMOD::System_Create(&FMODSystem) != FMOD_OK)
		throw;

	FMODSystem->init(512, FMOD_INIT_NORMAL, 0);
}

void AudioController::Shutdown()
{
	FMODSystem->release();
}

bool AudioController::LoadAudio(std::string path, bool looping)
{
	FMOD::Sound* sound;

	FMOD_RESULT result;

	std::string fullPath = SOLUTION_DIR + path;

	if ((result = FMODSystem->createSound(fullPath.c_str(), FMOD_2D, nullptr, &sound)) != FMOD_OK)
	{
		Debug::LogError("[Load Audio][%s] FMOD Error[%d]: %s ", path, result, FMOD_ErrorString(result));
		return false;
	}

	AssetManager::AddAudio(path, new CAudio(sound, nullptr));
	return true;
}

bool AudioController::PlayAudio(std::string path)
{
	CAudio* audio = AssetManager::GetAudio(path);
	FMOD_RESULT result;

	if(audio == nullptr)
	{
		Debug::Log("[Play Audio][%s] Tried to play audio that isnt loaded!", path);
		return false;
	}

	// Play Audio.
	if ((result = FMODSystem->playSound(audio->sound, nullptr, false, &audio->channel)) != FMOD_OK)
	{
		Debug::LogError("[Play Audio][%s] FMOD Error[%d]: %s ", path, result, FMOD_ErrorString(result));
		return false;
	}

	return true;
}

bool AudioController::StopAudio(std::string path)
{
	CAudio* audio = AssetManager::GetAudio(path);
	FMOD_RESULT result;

	bool isPlaying;
	audio->channel->isPlaying(&isPlaying);

	// See if it is playing on a channel.
	if (audio->channel != nullptr && isPlaying)
	{
		// Stop it on that channel.
		if ((result = audio->channel->stop()) != FMOD_OK)
		{
			Debug::LogError("[Stop Audio][%s] FMOD Error[%d]: %s ", path, result, FMOD_ErrorString(result));
			return false;
		}
	}

	return true;
}

bool AudioController::DestroyAudio(std::string path)
{
	FMOD_RESULT result;
	CAudio* audio = AssetManager::GetAudio(path);

	StopAudio(path);

	if(audio->sound != nullptr)
	{
		if((result = audio->sound->release()) != FMOD_OK)
		{
			Debug::LogError("[Destroy Audio][%s]FMOD Error[%d]: %s ", path, result, FMOD_ErrorString(result));
			return false;
		}
	}

	AssetManager::RemoveAudio(path);
	return true;
}
