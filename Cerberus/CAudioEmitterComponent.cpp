#include "CAudioEmitterComponent.h"

CAudioEmitterComponent::CAudioEmitterComponent()
{
	shouldUpdate = true;
	shouldDraw = false;
	ui = false;

	emitter = new CEmitter();
}

CAudioEmitterComponent::~CAudioEmitterComponent()
{
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

void CAudioEmitterComponent::Update(float deltaTime)
{
	emitter->position = this->GetPosition(); // Change this to the parent thing once we pull.
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
