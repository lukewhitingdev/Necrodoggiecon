#include "SoundManager.h"
#include "Cerberus/Core/Engine.h"
/*****************************************************************//**
 * \file   SoundManager.cpp
 * \brief  Static class used to handle the playing of audio within the game.
 *
 * \author Cathan Bertram
 * \date   May 2022
 *********************************************************************/

std::map<std::string, AudioEmitterEntity*> SoundManager::audioEmitterMap;
AudioEmitterEntity* SoundManager::musicAudioEmitter = nullptr;
/**
 * Function to initialise the SoundManager by creating audio emitters for each sound that will be used within the game.
 * 
 */
void SoundManager::Initialise()
{
	musicAudioEmitter = Engine::CreateEntity<AudioEmitterEntity>();

	AddSound("Resources/Game/Audio/DeathSound.wav", "DeathSound", 1000.0f, true);
	AddSound("Resources/Game/Audio/Footstep.wav", "StepSound", 100, true);
	AddSound("Resources/Game/Audio/ShieldHit.wav", "ShieldHit", 1000.0f, true);
	AddSound("Resources/Game/Audio/DeactivateInvis.wav", "DeactivateInvis", 1000.0f, true);
	AddSound("Resources/Game/Audio/Bell.wav", "Bell", 1000.0f);
	AddSound("Resources/Game/Audio/DogBark.wav", "DogBark", 1000.0f, true);
	AddSound("Resources/Game/Audio/ItemPickup.wav", "ItemPickup", 10.0f, true);
	AddSound("Resources/Game/Audio/DaggerStab.wav", "DaggerStab", 1000.0f, true);
	AddSound("Resources/Game/Audio/DaggerThrust.wav", "DaggerThrust", 1000.0f);
	AddSound("Resources/Game/Audio/RapierHit.wav", "RapierHit", 1000.0f, true);
	AddSound("Resources/Game/Audio/RapierThrust.wav", "RapierThrust", 1000.0f);
	AddSound("Resources/Game/Audio/BroadswordHit.wav", "BroadswordHit", 1000.0f, true);
	AddSound("Resources/Game/Audio/BroadswordSwing.wav", "BroadswordSwing", 1000.0f);
	AddSound("Resources/Game/Audio/ArrowHit1.wav", "ArrowHit", 1000.0f, true);
	AddSound("Resources/Game/Audio/ShootBow.wav", "ShootBow", 1000.0f);
	AddSound("Resources/Game/Audio/KnifeThrow.wav", "KnifeThrow", 1000.0f);
	AddSound("Resources/Game/Audio/FireballKill.wav", "FireballHit", 1000.0f, true);
	AddSound("Resources/Game/Audio/FireballShoot.wav", "FireballShoot", 1000.0f);
	AddSound("Resources/Game/Audio/ScrollActivate.wav", "ScrollActivate", 1000.0f, true);
	AddSound("Resources/Game/Audio/MagicMissileShoot.wav", "MagicMissileShoot", 1000.0f);
	AddSound("Resources/Game/Audio/Click.wav", "UIClick", FLT_MAX, true);
	AddSound("Resources/Game/Audio/ClearLevel.wav", "LevelClear", 1000.0f, true);
}
/**
 * Function to add a new audio emitter to the SoundManager.
 * 
 * \param audioPath - Path to the audio file
 * \param audioName - Name to store in the map with the emitter
 * \param audioRange - The range of the audio
 */
void SoundManager::AddSound(const std::string& audioPath, const std::string& audioName, float audioRange)
{
	AudioEmitterEntity* emitterEntity = Engine::CreateEntity<AudioEmitterEntity>();
	emitterEntity->SetAudio(audioPath, audioRange);
	audioEmitterMap.emplace(audioName, emitterEntity);
}
/**
 * Function to add a new audio emitter to the SoundManager.
 *
 * \param audioPath - Path to the audio file
 * \param audioName - Name to store in the map with the emitter
 * \param audioRange - The range of the audio
 * \param ambient - Whether the audio should be ambient or not
 */
void SoundManager::AddSound(const std::string& audioPath, const std::string& audioName, float audioRange, bool ambient)
{
	AudioEmitterEntity* emitterEntity = Engine::CreateEntity<AudioEmitterEntity>();
	emitterEntity->SetAudio(audioPath, audioRange, ambient);
	audioEmitterMap.emplace(audioName, emitterEntity);
}
/**
 * Function to play audio from one of the audio emitters stored in the SoundManager.
 * 
 * \param audioName - The name associated with the audio emitter
 * \param position - The position to play the audio at
 */
void SoundManager::PlaySound(const std::string& audioName, Vector3 position)
{
	if (audioEmitterMap.find(audioName) == audioEmitterMap.end()) {
		std::string errorMessage = "Audio with name: " + audioName + " does not exist in audioEmitterMap";
		Debug::LogError(errorMessage.c_str());
		return;
	}
	audioEmitterMap[audioName]->PlayAudio(position);
}
/**
 * Function used to play music.
 * 
 * \param musicPath - Path to the audio file containing the correct music
 * \param attachedEntity - The entity that the music should follow to ensure it can always be heard
 */
void SoundManager::PlayMusic(const std::string& musicPath, CEntity* attachedEntity)
{
	if (musicAudioEmitter == nullptr)
		musicAudioEmitter = Engine::CreateEntity<AudioEmitterEntity>();
	if(attachedEntity != nullptr)
		musicAudioEmitter->SetAttachedEntity(attachedEntity);
	musicAudioEmitter->Stop();
	musicAudioEmitter->Load(musicPath, true);
	musicAudioEmitter->SetRange(FLT_MAX);
	musicAudioEmitter->PlayAudio(true);
}
