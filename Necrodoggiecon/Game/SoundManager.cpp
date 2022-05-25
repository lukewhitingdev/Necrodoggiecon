#include "SoundManager.h"

std::map<std::string, AudioEmitterEntity*> SoundManager::audioEmitterMap;

void SoundManager::Initialise()
{
	AddSound("Resources/Game/Audio/DeathSound.wav", "DeathSound", 10000.0f);
	AddSound("Resources/Game/Audio/Footstep.wav", "StepSound", 10000.0f);
	AddSound("Resources/Game/Audio/ShieldHit.wav", "ShieldHit", 10000.0f);
	AddSound("Resources/Game/Audio/DeactivateInvis.wav", "DeactivateInvis", 10000.0f);
	AddSound("Resources/Game/Audio/Bell.wav", "Bell", 10000.0f);
	AddSound("Resources/Game/Audio/DogBark.wav", "DogBark", 10000.0f);
	AddSound("Resources/Game/Audio/ItemPickup.wav", "ItemPickup", 10000.0f);
	AddSound("Resources/Game/Audio/DaggerStab.wav", "DaggerStab", 10000.0f);
	AddSound("Resources/Game/Audio/DaggerThrust.wav", "DaggerThrust", 10000.0f);
	AddSound("Resources/Game/Audio/RapierHit.wav", "RapierHit", 10000.0f);
	AddSound("Resources/Game/Audio/RapierThrust.wav", "RapierThrust", 10000.0f);
	AddSound("Resources/Game/Audio/BroadswordHit.wav", "BroadswordHit", 10000.0f);
	AddSound("Resources/Game/Audio/BroadswordSwing.wav", "BroadswordSwing", 10000.0f);
	AddSound("Resources/Game/Audio/ArrowHit1.wav", "ArrowHit", 10000.0f);
	AddSound("Resources/Game/Audio/ShootBow.wav", "ShootBow", 10000.0f);
	AddSound("Resources/Game/Audio/KnifeThrow.wav", "KnifeThrow", 10000.0f);
	AddSound("Resources/Game/Audio/FireballKill.wav", "FireballHit", 10000.0f);
	AddSound("Resources/Game/Audio/FireballShoot.wav", "FireballShoot", 10000.0f);
	AddSound("Resources/Game/Audio/ScrollActivate.wav", "ScrollActivate", 10000.0f);
}

void SoundManager::AddSound(const std::string& audioPath, const std::string& audioName, float audioRange)
{
	AudioEmitterEntity* emitterEntity = Engine::CreateEntity<AudioEmitterEntity>();
	emitterEntity->SetAudio(audioPath, audioRange);
	audioEmitterMap.emplace(audioName, emitterEntity);
}

void SoundManager::PlaySound(const std::string& audioName, Vector3 position)
{
	if (audioEmitterMap.find(audioName) == audioEmitterMap.end()) {
		std::string errorMessage = "Audio with name: " + audioName + " does not exist in audioEmitterMap";
		Debug::LogError(errorMessage.c_str());
		return;
	}
	audioEmitterMap[audioName]->PlayAudio(position);
}
