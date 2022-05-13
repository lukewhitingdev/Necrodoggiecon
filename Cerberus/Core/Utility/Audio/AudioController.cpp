/*****************************************************************//**
 * \file   AudioController.cpp
 * \brief  Internal Audio Controller for the engine.
 * 
 * \author Luke Whiting
 * \date   Jan 2022
 *********************************************************************/
#include "AudioController.h"
#include "Cerberus\Core\Utility\EventSystem\EventSystem.h"
FMOD::System* AudioController::FMODSystem;
std::vector<CEmitter*> AudioController::emitters;

/**
 * Initializes the audio system and FMOD.
 * 
 */
void AudioController::Initialize()
{
	if (FMOD::System_Create(&FMODSystem) != FMOD_OK)
		throw;

	FMODSystem->init(512, FMOD_INIT_NORMAL, 0);

	FMODSystem->set3DSettings(0, 1, 1);

	FMODSystem->set3DNumListeners(1);
}

/**
 * Shutsdown the audio system and FMOD.
 * 
 */
void AudioController::Shutdown()
{
	FMODSystem->release();
}

/**
 * Loads a audio into FMOD and the audio system
 * 
 * \param path
 * \return 
 */
CAudio* AudioController::LoadAudio(std::string path)
{
	if (FMODSystem == nullptr)
		Initialize();

	FMOD::Sound* sound;

	FMOD_RESULT result;

	if ((result = FMODSystem->createSound(path.c_str(), FMOD_2D, nullptr, &sound)) != FMOD_OK)
	{
		Debug::LogError("[Load Audio][%s] FMOD Error[%d]: %s ", path.c_str(), result, FMOD_ErrorString(result));
		return nullptr;
	}

	sound->set3DMinMaxDistance(0, 1000);

	return AssetManager::AddAudio(path, new CAudio(path,sound, nullptr));
}

/**
 * Plays a audio using FMOD.
 * 
 * \param path
 * \return 
 */
bool AudioController::PlayAudio(std::string path)
{
	if (FMODSystem == nullptr)
		Initialize();

	CAudio* audio = AssetManager::GetAudio(path);
	FMOD_RESULT result;

	if(audio == nullptr)
	{
		Debug::Log("[Play Audio][%s] Tried to play audio that isnt loaded!", path.c_str());
		return false;
	}

	// Play Audio.
	if ((result = FMODSystem->playSound(audio->sound, nullptr, false, &audio->channel)) != FMOD_OK)
	{
		Debug::LogError("[Play Audio][%s] FMOD Error[%d]: %s ", path.c_str(), result, FMOD_ErrorString(result));
		return false;
	}

	EventSystem::TriggerEvent("soundPlayed");

	return true;
}

/**
 * Stops a audio from playing.
 * 
 * \param path
 * \return 
 */
bool AudioController::StopAudio(std::string path)
{
	if (FMODSystem == nullptr)
		Initialize();

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
			Debug::LogError("[Stop Audio][%s] FMOD Error[%d]: %s ", path.c_str(), result, FMOD_ErrorString(result));
			return false;
		}
	}

	return true;
}

/**
 * Deletes a audio from FMOD and the audio system.
 * 
 * \param path
 * \return 
 */
bool AudioController::DestroyAudio(std::string path)
{
	if (FMODSystem == nullptr)
		Initialize();

	FMOD_RESULT result;
	CAudio* audio = AssetManager::GetAudio(path);

	StopAudio(path);

	if(audio->sound != nullptr)
	{
		if((result = audio->sound->release()) != FMOD_OK)
		{
			Debug::LogError("[Destroy Audio][%s]FMOD Error[%d]: %s ", path.c_str(), result, FMOD_ErrorString(result));
			return false;
		}
	}

	AssetManager::RemoveAudio(path);
	return true;
}

/** Updates the overall audio volume to simulate 3D audio. */
void AudioController::Update(Vector3 listenerPos, float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (FMODSystem == nullptr)
		AudioController::Initialize();

	FMOD_RESULT result;

	// Attenuate.
	float maxRange = 1000;
	for(CEmitter* emitter : emitters)
	{

		float distToEmitter = listenerPos.DistanceTo(emitter->position);

		// Check we are in range of the emitter.
		if (distToEmitter > emitter->range)
			continue;

		float attentuation = 1 - (distToEmitter / maxRange);

		// Clamp because im bad at math.
		if(attentuation < 0)
		{
			attentuation = 0;
		}

		// Attenuate.
		emitter->audio->channel->setVolume(attentuation);
	}


	if ((result = FMODSystem->update()) != FMOD_OK)
	{
		Debug::LogError("[Audio Update] FMOD Error[%d]: %s ", result, FMOD_ErrorString(result));
		return;
	}
}

/**
 * Returns all emitters within range of a position.
 * 
 * \param position
 * \return 
 */
std::vector<CEmitter*> AudioController::GetAllEmittersWithinRange(Vector3 position)
{
	std::vector<CEmitter*> output;
	for(CEmitter* emiter : emitters)
	{
		// Check if we are inrange of the circular range emitters have.
		if (emiter->range > position.DistanceTo(emiter->position))
			output.emplace_back(emiter);
	}
	return output;
}

/**
 * Adds a emitter to the audio system.
 * 
 * \param emitter
 */
void AudioController::AddEmitter(CEmitter* emitter)
{
	emitters.emplace_back(emitter);
}

/**
 * Removes a emitter from the audio system.
 * 
 * \param emitter
 */
void AudioController::RemoveEmitter(CEmitter* emitter)
{
	for (size_t i = 0; i < emitters.size(); i++)
	{
		CEmitter* emiter = emitters[i];
		if(emiter == emitter)
		{
			emitters.erase(emitters.begin() + i);
			break;
		}
	}

	delete emitter;
}
