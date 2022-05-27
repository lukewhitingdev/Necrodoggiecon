#include "AudioEmitterEntity.h"
/*****************************************************************//**
 * \file   AudioEmitterEntity.cpp
 * \brief  An entity that contains an audio emitter. Used in the SoundManager to enable the playing of audio at specific positions.
 * 
 * \author Cathan Bertram
 * \date   May 2022
 *********************************************************************/

#include "SoundManager.h"
AudioEmitterEntity::AudioEmitterEntity()
{
	audioEmitter = AddComponent<CAudioEmitterComponent>(NAME_OF(audioEmitter));
}

AudioEmitterEntity::~AudioEmitterEntity()
{
	SoundManager::RemoveSound(audioName);
}
/**
 * Function to set the audio that the emitter should store.
 * 
 * \param audioPath - Path to the audio file
 * \param range - The range of the audio
 * \param ambient - Whether the audio is ambient or not
 */
void AudioEmitterEntity::SetAudio(const std::string& audioPath, float range, bool ambient)
{
	audioEmitter->Load(audioPath, ambient);
	audioEmitter->SetRange(range);
}
/**
 * Function to set the audio that the emitter should store.
 *
 * \param audioPath - Path to the audio file
 * \param range - The range of the audio
 */
void AudioEmitterEntity::SetAudio(const std::string& audioPath, float range)
{
	audioEmitter->Load(audioPath);
	audioEmitter->SetRange(range);
}
/**
 * Function to play the stored audio at the appropriate position.
 * 
 * \param position - The position to play the audio at
 */
void AudioEmitterEntity::PlayAudio(Vector3 position)
{
	SetPosition(position);
	audioEmitter->Play();
}
/**
 * Function to stop the audio emitter from playing.
 * 
 */
void AudioEmitterEntity::Stop()
{
	audioEmitter->Stop();
}
/**
 * Function to load and play audio from a file path.
 * 
 * \param audioPath - Path to the audio file
 */
void AudioEmitterEntity::PlayAudio(const std::string& audioPath)
{
	audioEmitter->Load(audioPath);
	audioEmitter->Play();
}
/**
 * Function to play the stored audio.
 * 
 * \param shouldLoop - Whether or not the audio should loop
 */
void AudioEmitterEntity::PlayAudio(bool shouldLoop)
{
	audioEmitter->Play(shouldLoop);
}
/**
 * Function to load audio from a file.
 * 
 * \param audioPath - Path to the audio file
 * \param ambient - Whether or not the audio is ambient
 */
void AudioEmitterEntity::Load(const std::string& audioPath, bool ambient)
{
	audioEmitter->Load(audioPath, ambient);
}
/**
 * Funtion to set the range of the audio.
 * 
 * \param range - The new range for the audio emitter
 */
void AudioEmitterEntity::SetRange(float range)
{
	audioEmitter->SetRange(range);
}
/**
 * Function inherited from CEntity.
 * Used to ensure the Entity follows the attached entities position
 * 
 * \param deltaTime - Time since the last frame
 */
void AudioEmitterEntity::Update(float deltaTime)
{
	if (isAttached)
		SetPosition(attachedEntity->GetPosition());
}
