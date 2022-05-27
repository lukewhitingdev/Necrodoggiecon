#include "CAudioEmitterComponent.h"
#include "Cerberus\Core\CEntity.h"

CAudioEmitterComponent::CAudioEmitterComponent()
{
	SetShouldUpdate(true);
	SetShouldDraw(false);
	SetIsUI(false);

	emitter = new CEmitter();
}

CAudioEmitterComponent::~CAudioEmitterComponent()
{
	this->Stop();
	if(!AudioController::RemoveEmitter(emitter))
	{
		Debug::LogError("An error has occured whilst destructing the audio emitter component. See error above. (%s)", GetDebugInfo().c_str());
		return;
	}
}

/**
 * Loads a audio to be used by the emitter.
 *
 * \param path path to audio
 */
void CAudioEmitterComponent::Load(const std::string& path)
{
	emitter->audio = AudioController::LoadAudio(path);

	emitter->type = EMITTERTYPE::SFX;

	if(emitter->audio != nullptr)
	{
		emitter->audio->path = path;

		if(!AudioController::AddEmitter(emitter))
		{
			Debug::LogError("An error has occured whilst adding a emitter to the audio controller. See error above. Path: %s (%s)", path.c_str(), GetDebugInfo().c_str());
			return;
		}
	}
	else
	{
		Debug::LogError("An error occured whilst loading the audio for an emitter. See error above. Path: %s (%s)", path.c_str(),GetDebugInfo().c_str());
		return;
	}
}

/**
 * Loads a audio to be used by the emitter.
 * 
 * \param path path to audio
 */
void CAudioEmitterComponent::Load(const std::string& path, bool ambient)
{
	emitter->audio = AudioController::LoadAudio(path);

	emitter->type = (ambient) ? EMITTERTYPE::AMBIENT : EMITTERTYPE::SFX;

	if (emitter->audio != nullptr)
	{
		emitter->audio->path = path;

		if (!AudioController::AddEmitter(emitter))
		{
			Debug::LogError("An error has occured whilst adding a emitter to the audio controller. See error above. Path: %s (%s)", path.c_str(), GetDebugInfo().c_str());
			return;
		}
	}
	else
	{
		Debug::LogError("An error occured whilst loading the audio for an emitter. See error above. Path: %s (%s)", path.c_str(), GetDebugInfo().c_str());
		return;
	}
}

/**
 * Sets the range at which the audio can be heard.
 * 
 * \param range hearing distance of audio.
 */
void CAudioEmitterComponent::SetRange(float range)
{
	emitter->range = range;

	if(emitter->audio != nullptr)
	{
		FMOD_RESULT result = emitter->audio->sound->set3DMinMaxDistance(0, range);
		if(result != FMOD_OK)
		{
			Debug::LogError("An error occured whilst setting the range of a emitter. FMOD_ERROR: %s", FMOD_ErrorString(result));
			return;
		}
	}
	else
	{
		Debug::LogError("Tried to set the range of a emitter without loading any audio into the emitter, this is required to be done before setting the range. (%s)", GetDebugInfo().c_str());
		return;
	}

}

/**
 * Updates the audio emitters position.
 * 
 * \param deltaTime
 */
void CAudioEmitterComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	emitter->position = this->GetParent()->GetPosition();
}

/**
 * Plays the audio emitter.
 * 
 */
void CAudioEmitterComponent::Play()
{
	if (emitter->audio != nullptr)
	{
		if(!AudioController::PlayAudio(emitter->audio->path))
		{
			Debug::LogError("An error occured whils trying to play audio on a emitter, see error above.");
			return;
		}
	}
	else
	{
		Debug::LogError("Tried to play audio on a emitter without having a loaded audio. This is not allowed.");
		return;
	}
}

/**
 * Plays the audio emitter with a option of looping the audio.
 * 
 * \param loop
 */
void CAudioEmitterComponent::Play(bool loop)
{
	if (emitter->audio != nullptr)
	{
		if (!AudioController::PlayAudio(emitter->audio->path, loop))
		{
			Debug::LogError("An error occured whils trying to play audio on a emitter, see error above.");
			return;
		}
	}
	else
	{
		Debug::LogError("Tried to play audio on a emitter without having a loaded audio. This is not allowed.");
		return;
	}
}

/**
 * Stops the audio emitter.
 * 
 */
void CAudioEmitterComponent::Stop()
{
	if (emitter->audio != nullptr)
	{
		if(!AudioController::StopAudio(emitter->audio->path))
		{
			Debug::LogError("An error occured whils trying to stop audio on a emitter, see error above.");
			return;
		}
	}
	else
	{
		Debug::LogError("Tried to stop audio on a emitter without having a loaded audio. This is not allowed.");
		return;
	}
}
