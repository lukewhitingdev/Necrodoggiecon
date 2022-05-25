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
	AudioController::RemoveEmitter(emitter);
}

/**
 * Loads a audio to be used by the emitter.
 *
 * \param path path to audio
 */
void CAudioEmitterComponent::Load(const std::string& path)
{
	emitter->audio = AudioController::LoadAudio(path);
	emitter->audio->path = path;

	AudioController::AddEmitter(emitter);
}

/**
 * Loads a audio to be used by the emitter.
 * 
 * \param path path to audio
 */
void CAudioEmitterComponent::Load(const std::string& path, bool ambient)
{
	emitter->audio = AudioController::LoadAudio(path);
	emitter->audio->path = path;

	AudioController::AddEmitter(emitter, ambient);
}

/**
 * Sets the range at which the audio can be heard.
 * 
 * \param range hearing distance of audio.
 */
void CAudioEmitterComponent::SetRange(float range)
{
	emitter->range = range;
	emitter->audio->sound->set3DMinMaxDistance(0, range);
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
		AudioController::PlayAudio(emitter->audio->path);
	else
		AudioController::PlayAudio(""); // Trigger Audio is not loaded error.
}

/**
 * Stops the audio emitter.
 * 
 */
void CAudioEmitterComponent::Stop()
{
	if (emitter->audio != nullptr)
		AudioController::StopAudio(emitter->audio->path);
}
