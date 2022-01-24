#include "CAudioEmitterComponent.h"

CAudioEmitterComponent::CAudioEmitterComponent()
{
	shouldUpdate = true;
	shouldDraw = false;
	ui = false;

	emitter = new CEmitter();

	fmodPosition = new FMOD_VECTOR();
	fmodPreviousPosition = new FMOD_VECTOR();
	fmodVelocity = new FMOD_VECTOR();

	this->SetPosition(0, 0, 0);
}

CAudioEmitterComponent::~CAudioEmitterComponent()
{
	delete fmodPosition;
	delete fmodPreviousPosition;

	AudioController::removeEmitter(emitter);
}

void CAudioEmitterComponent::Load(std::string path)
{
	emitter->audio = AudioController::LoadAudio(path, false);
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

	if (emitter->audio != nullptr) 
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

		Debug::Log("Emitter Location: x:%f(%f), y:%f(%f), z:%f(%f)", 
			fmodPosition->x,fmodVelocity->x,
			fmodPosition->y,fmodVelocity->y,
			fmodPosition->z, fmodVelocity->z);

		// Set Previous Position up for the next call.
		fmodPreviousPosition = fmodPosition;

		// Could use this? https://www.fmod.com/resources/documentation-api?version=2.02&page=core-api-channelcontrol.html#channelcontrol_set3dlevel
		// https://www.fmod.com/resources/documentation-api?version=2.02&page=core-guide.html#3d-sound-and-spatialization
		// Set 3D Attributes
		if ((result = emitter->audio->channel->set3DAttributes(fmodPosition, fmodVelocity)) != FMOD_OK && !isnan(fmodPosition->x) && !isnan(fmodVelocity->x))
		{
			Debug::LogError("[CAudioEmitterComponent] FMOD Error setting 3D Attributes! [%d]: %s ", result, FMOD_ErrorString(result));
			return;
		}
	}
}
