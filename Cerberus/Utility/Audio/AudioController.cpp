#include "AudioController.h"
FMOD::System* AudioController::FMODSystem;

void AudioController::Initialize()
{
	if (FMOD::System_Create(&FMODSystem) != FMOD_OK)
		throw;

	FMODSystem->init(512, FMOD_INIT_NORMAL, 0);

	FMODSystem->set3DSettings(0, 1, 1);

	FMODSystem->set3DNumListeners(1);
}

void AudioController::Shutdown()
{
	FMODSystem->release();
}

bool AudioController::LoadAudio(std::string path, bool worldSpace)
{
	FMOD::Sound* sound;

	FMOD_RESULT result;

	std::string fullPath = SOLUTION_DIR + path;

	if ((result = FMODSystem->createSound(fullPath.c_str(), (worldSpace) ? FMOD_3D : FMOD_2D, nullptr, &sound)) != FMOD_OK)
	{
		Debug::LogError("[Load Audio][%s] FMOD Error[%d]: %s ", path, result, FMOD_ErrorString(result));
		return false;
	}
	sound->set3DMinMaxDistance(0, 20000);

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

	static FMOD_VECTOR* posVec;
	static FMOD_VECTOR* prevPosVec;
	static FMOD_VECTOR* velVec;

	if (posVec == nullptr)
	{
		posVec = new FMOD_VECTOR();
		prevPosVec = new FMOD_VECTOR();
	}

	if(velVec == nullptr)
	{
		velVec = new FMOD_VECTOR();
	}

	posVec->x = 0;
	posVec->y = 0;
	posVec->z = 0;

	float deltaTime = 0.16;

	velVec->x = 1;
	velVec->y = 1;
	velVec->z = 1;

	if (prevPosVec != posVec)
		prevPosVec = posVec;

	audio->channel->set3DAttributes(posVec, velVec);

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

void AudioController::Update(Vector3 listenerPos, float deltaTime)
{
	static FMOD_VECTOR* posVec;
	static FMOD_VECTOR* prevPosVec;
	static FMOD_VECTOR* velVec;
	static FMOD_VECTOR* forwardVec;
	static FMOD_VECTOR* upVec;

	if(posVec == nullptr)
	{
		posVec = new FMOD_VECTOR();
		prevPosVec = new FMOD_VECTOR();
	}

	if (velVec == nullptr)
		velVec = new FMOD_VECTOR();

	if (forwardVec == nullptr)
		forwardVec = new FMOD_VECTOR();

	if (upVec == nullptr)
		upVec = new FMOD_VECTOR();

	FMOD_RESULT result;
	posVec->x = listenerPos.x;
	posVec->y = listenerPos.y;
	posVec->z = listenerPos.z;

	velVec->x = (posVec->x - prevPosVec->x) * 1000 / deltaTime;
	velVec->y = (posVec->y - prevPosVec->y) * 1000 / deltaTime;
	velVec->z = (posVec->z - prevPosVec->z) * 1000 / deltaTime;

	if (prevPosVec != posVec)
		prevPosVec = posVec;

	forwardVec->x = 0;
	forwardVec->y = 0;
	forwardVec->z = 1;

	upVec->x = 0;
	upVec->y = 1;
	upVec->z = 0;

	if ((result = FMODSystem->set3DListenerAttributes(0, posVec, velVec, forwardVec, upVec)) != FMOD_OK)
	{
		Debug::LogError("[Audio Update] FMOD Error[%d]: %s ", result, FMOD_ErrorString(result));
		return;
	}

	if ((result = FMODSystem->update()) != FMOD_OK)
	{
		Debug::LogError("[Audio Update] FMOD Error[%d]: %s ", result, FMOD_ErrorString(result));
		return;
	}
}
