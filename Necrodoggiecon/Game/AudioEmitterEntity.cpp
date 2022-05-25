#include "AudioEmitterEntity.h"

AudioEmitterEntity::AudioEmitterEntity()
{
	audioEmitter = AddComponent<CAudioEmitterComponent>(NAME_OF(audioEmitter));
}

AudioEmitterEntity::~AudioEmitterEntity()
{
}

void AudioEmitterEntity::SetAudio(const std::string audioPath, float range)
{
	audioEmitter->Load(audioPath);
	audioEmitter->SetRange(range);
}

void AudioEmitterEntity::PlayAudio(Vector3 position)
{
	SetPosition(position);
	audioEmitter->Play();
}

void AudioEmitterEntity::Update(float deltaTime)
{
}
