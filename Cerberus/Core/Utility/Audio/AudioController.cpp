#include "AudioController.h"
#include "Cerberus\Core\Utility\EventSystem\EventSystem.h"
FMOD::System* AudioController::FMODSystem = nullptr;
std::vector<CEmitter*> AudioController::emitters;
std::unordered_map<std::uintptr_t, CEmitter*> AudioController::emitterSafetyMap;
CTransform* AudioController::listenerTransform = nullptr;

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
	emitters.clear();
}

/**
 * Loads a audio into FMOD and the audio system
 * 
 * \param path to audio you wish to load.
 * \return CAudio pointer to the created audio.
 */
CAudio* AudioController::LoadAudio(const std::string& path)
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
 * \param path to audio you wish to play.
 * \return bool on success or failure.
 */
bool AudioController::PlayAudio(const std::string& path)
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

	if ((result = audio->sound->setLoopCount(0)) != FMOD_OK)
	{
		Debug::LogError("[Play Audio][%s] FMOD Error when setting loop count back to zero [%d]: %s ", path.c_str(), result, FMOD_ErrorString(result));
		return false;
	}

	if ((result = audio->sound->setMode(FMOD_LOOP_OFF)) != FMOD_OK)
	{
		Debug::LogError("[Play Audio][%s] FMOD Error when setting loop mode [%d]: %s ", path.c_str(), result, FMOD_ErrorString(result));
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
 * Plays a audio using FMOD with the ability to loop.
 *
 * \param path to audio you wish to play
 * \param loop whether you would like the audio to loop.
 * \return bool on success or failure.
 */
bool AudioController::PlayAudio(const std::string& path, bool loop)
{
	if (FMODSystem == nullptr)
		Initialize();

	CAudio* audio = AssetManager::GetAudio(path);
	FMOD_RESULT result;

	if (audio == nullptr)
	{
		Debug::Log("[Play Audio][%s] Tried to play audio that isnt loaded!", path.c_str());
		return false;
	}

	if(loop)
	{
		if ((result = audio->sound->setLoopCount(-1)) != FMOD_OK)
		{
			Debug::LogError("[Play Audio][%s] FMOD Error when setting loop count [%d]: %s ", path.c_str(), result, FMOD_ErrorString(result));
			return false;
		}

		if ((result = audio->sound->setMode(FMOD_LOOP_NORMAL)) != FMOD_OK)
		{
			Debug::LogError("[Play Audio][%s] FMOD Error when setting loop mode [%d]: %s ", path.c_str(), result, FMOD_ErrorString(result));
			return false;
		}
	}
	else
	{
		if ((result = audio->sound->setLoopCount(0)) != FMOD_OK)
		{
			Debug::LogError("[Play Audio][%s] FMOD Error when setting loop count back to zero [%d]: %s ", path.c_str(), result, FMOD_ErrorString(result));
			return false;
		}

		if ((result = audio->sound->setMode(FMOD_LOOP_OFF)) != FMOD_OK)
		{
			Debug::LogError("[Play Audio][%s] FMOD Error when setting loop mode [%d]: %s ", path.c_str(), result, FMOD_ErrorString(result));
			return false;
		}
	}


	// Play Audio.
	if ((result = FMODSystem->playSound(audio->sound, nullptr, false, &audio->channel)) != FMOD_OK)
	{
		Debug::LogError("[Play Audio][%s] FMOD Error when playing audio [%d]: %s ", path.c_str(), result, FMOD_ErrorString(result));
		return false;
	}

	EventSystem::TriggerEvent("soundPlayed");

	return true;
}

/**
 * Stops a audio from playing.
 * 
 * \param path to audio you wish to stop playing.
 * \return bool on success or failure
 */
bool AudioController::StopAudio(const std::string& path)
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
 * \param path to audio that you wish to destroy
 * \return bool on success or failure
 */
bool AudioController::DestroyAudio(const std::string& path)
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
void AudioController::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	Vector3 listenerPos = Vector3(0, 0, 0);

	if (FMODSystem == nullptr)
		AudioController::Initialize();

	if (listenerTransform != nullptr)
		listenerPos = listenerTransform->GetPosition();

	FMOD_RESULT result;

	// Attenuate.
	float maxRange = 1000;
	for(int i = 0; i < emitters.size(); ++i)
	{
		CEmitter* emitter = emitters[i];
		float distToEmitter = listenerPos.DistanceTo(emitter->position);

		// Check we are in range of the emitter.
		if (distToEmitter > emitter->range)
		{
			emitter->audio->channel->setVolume(0);
			continue;
		}

		float attentuation = 1 - (distToEmitter / maxRange);

		if(attentuation > (emitter->audio->maxVolume / 100))
		{
			attentuation = (emitter->audio->maxVolume / 100);
		}

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
 * \param position sampling position, should be at the center of the search area.
 * \return a vector of emitters that where in range and satisfied the argument conditions.
 */
std::vector<CEmitter*> AudioController::GetAllEmittersWithinRange(Vector3 position, bool checkIfPlaying)
{
	std::vector<CEmitter*> output;
	for (CEmitter* emiter : emitters)
	{
		if(emiter->type != EMITTERTYPE::AMBIENT)
		{
			// Check if we are inrange of the circular range emitters have.
			if (emiter->range > position.DistanceTo(emiter->position))
			{
				if (checkIfPlaying)
				{
					bool isPlaying = false;
					FMOD_RESULT result;

					if (emiter->audio->channel != nullptr)
					{
						if ((result = emiter->audio->channel->isPlaying(&isPlaying)) != FMOD_OK)
						{
							Debug::LogError("An Error Occured when trying to get emitter that in range that is playing. Path: %s, FMOD Error: ", emiter->audio->path.c_str(), FMOD_ErrorString(result));
						}

						if (isPlaying)
						{
							output.emplace_back(emiter);
						}
					}
					else
					{
						output.emplace_back(emiter);
					}
				}
			}
		}
	}
	return output;
}

/**
 * Adds a emitter to the audio system.
 * 
 * \param emitter emitter you wish to add to the audio system.
 * \return bool on success or failure
 */
bool AudioController::AddEmitter(CEmitter* emitter)
{
	if(emitter != nullptr)
	{
		if(emitterSafetyMap.find((uintptr_t)emitter) != emitterSafetyMap.end())
		{
			Debug::LogError("Tried to add a emitter that already exists. This is not allowed.");
			return false;
		}

		emitters.emplace_back(emitter);
		emitterSafetyMap.emplace(std::make_pair((uintptr_t)emitter, emitter));
		return true;
	}
	else
	{
		Debug::LogError("Tried to add emitter to audio controller that is nullptr!.");
		return false;
	}
}

/**
 * Removes a emitter from the audio system.
 * 
 * \param emitter emitter you wish to add to the audio system.
 * \return bool on success or failure
 */
bool AudioController::RemoveEmitter(CEmitter* emitter)
{
	if(emitter != nullptr)
	{
		bool found = false;
		for (size_t i = 0; i < emitters.size(); i++)
		{
			CEmitter* emiter = emitters[i];
			if (emiter == emitter)
			{
				emitters.erase(emitters.begin() + i);
				found = true;
				break;
			}
		}

		if(!found)
		{
			Debug::LogError("Could not find emitter to remove!");
			return false;
		}

		delete emitter;
		return true;
	}
	else
	{
		Debug::LogError("Tried to remove emitter to audio controller that is nullptr!.");
		return false;
	}
}

void AudioController::SetMaxVolumeForEmitterType(const float volume,EMITTERTYPE type)
{
	for(auto& emiter : emitters)
	{
		if(emiter->type == type || type == EMITTERTYPE::ALL)
		{
			emiter->audio->maxVolume = volume;
		}
	}
}

/**
 * Adds a listener to the audio controller, used for attenuation.
 * 
 * \param listenerPositon the position of the listener that controls the attenuation of the audio system.
 * \return bool on success or failure
 */
bool AudioController::AddListener(CTransform* listenerPos)
{
	if(listenerPos != nullptr)
	{
		AudioController::listenerTransform = listenerPos;
		return true;
	}
	else
	{
		Debug::LogError("Tried to set the audio controller listener position to a nullptr, this is not allowed.");
		return false;
	}
}
