#include "AudioEmitterEntity.h"

AudioEmitterEntity::AudioEmitterEntity()
{
	audioEmitter = AddComponent<CAudioEmitterComponent>(NAME_OF(audioEmitter));
}

AudioEmitterEntity::~AudioEmitterEntity()
{
}
void AudioEmitterEntity::SetAudio(const std::string& audioPath, float range, bool ambient)
{
	audioEmitter->Load(audioPath, ambient);
	audioEmitter->SetRange(range);
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

void AudioEmitterEntity::PlayAudio(bool shouldLoop)
{
	audioEmitter->Play(shouldLoop);
}

void AudioEmitterEntity::Load(const std::string& audioPath, bool ambient)
{
	audioEmitter->Load(audioPath, ambient);
}

void AudioEmitterEntity::SetLooping(bool looping)
{
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
