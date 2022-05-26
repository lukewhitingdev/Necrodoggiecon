#include "AudioEmitterEntity.h"

AudioEmitterEntity::AudioEmitterEntity()
{
	audioEmitter = AddComponent<CAudioEmitterComponent>(NAME_OF(audioEmitter));
}

AudioEmitterEntity::~AudioEmitterEntity()
{
}

void AudioEmitterEntity::SetAudio(const std::string& audioPath, float range)
{
	audioEmitter->Load(audioPath);
	audioEmitter->SetRange(range);
}

void AudioEmitterEntity::PlayAudio(Vector3 position)
{
	SetPosition(position);
	audioEmitter->Play();
}

void AudioEmitterEntity::Stop()
{
	audioEmitter->Stop();
}

void AudioEmitterEntity::PlayAudio(const std::string& audioPath)
{
	audioEmitter->Load(audioPath);
	audioEmitter->Play();
}

void AudioEmitterEntity::PlayAudio()
{
	audioEmitter->Play();
}

void AudioEmitterEntity::Load(const std::string& audioPath, bool ambient)
{
	audioEmitter->Load(audioPath, ambient);
}

bool AudioEmitterEntity::SetLooping()
{
	return false;
}

void AudioEmitterEntity::SetRange(float range)
{
	audioEmitter->SetRange(range);
}

void AudioEmitterEntity::Update(float deltaTime)
{
	if (isAttached)
		SetPosition(attachedEntity->GetPosition());
}
