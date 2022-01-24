#include "CAudioEmitterComponent.h"

CAudioEmitterComponent::CAudioEmitterComponent()
{
	shouldUpdate = true;
	shouldDraw = false;
	ui = false;

	emitter = new CEmitter();

	fmodPosition = new FMOD_VECTOR();
	fmodPosition = { 0 };

	fmodPreviousPosition = new FMOD_VECTOR();
	fmodPreviousPosition = { 0 };

	fmodVelocity = new FMOD_VECTOR();
	fmodVelocity = { 0 };
}

CAudioEmitterComponent::~CAudioEmitterComponent()
{
	delete fmodPosition;
	delete fmodPreviousPosition;

	AudioController::removeEmitter(emitter);
}

void CAudioEmitterComponent::Load(std::string path)
{
	emitter->audio = AudioController::LoadAudio(path, true);
	emitter->audio->path = path;

	AudioController::addEmitter(emitter);
}

void CAudioEmitterComponent::SetRange(float range)
{
	emitter->range = range;
	emitter->audio->sound->set3DMinMaxDistance(0, range);
}

void CAudioEmitterComponent::Play()
{
	if (emitter->audio != nullptr)
		AudioController::PlayAudio(emitter->audio->path);
	else
		AudioController::PlayAudio(""); // Trigger Audio is not loaded error.
}

void CAudioEmitterComponent::Stop()
{
	if (emitter->audio != nullptr)
		AudioController::StopAudio(emitter->audio->path);
}

void CAudioEmitterComponent::Update(float deltaTime)
{
	FMOD_RESULT result;

	if (emitter->audio != nullptr && fmodPosition != nullptr && fmodVelocity != nullptr && fmodPreviousPosition != nullptr) 
	{
		// Update the emitter position.
		emitter->position = this->GetPosition();

		// Set Position to new updated position
		fmodPosition->x = this->GetPosition().x;
		fmodPosition->y = this->GetPosition().y;
		fmodPosition->z = this->GetPosition().z;

		// Calculate Velocity. (Difference from previous frame) * 1000 / time passed between frames.
		fmodVelocity->x = (fmodPosition->x - fmodPreviousPosition->x) * 1000 / deltaTime;
		fmodVelocity->y = (fmodPosition->y - fmodPreviousPosition->y) * 1000 / deltaTime;
		fmodVelocity->z = (fmodPosition->z - fmodPreviousPosition->z) * 1000 / deltaTime;

		// Set Previous Position up for the next call.
		fmodPreviousPosition = fmodPosition;

		// Set 3D Attributes
		emitter->audio->channel->set3DAttributes(fmodPosition, fmodVelocity);

		if ((result = emitter->audio->channel->set3DAttributes(fmodPosition, fmodVelocity)) != FMOD_OK)
		{
			Debug::LogError("[CAudioEmitterComponent] FMOD Error setting 3D Attributes! [%d]: %s ", result, FMOD_ErrorString(result));
			return;
		}
	}
}
