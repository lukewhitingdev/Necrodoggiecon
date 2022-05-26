#pragma once
#include "Cerberus\Core\CEntity.h"
#include <Game/AudioEmitterEntity.h>

class SoundManager :  public CEntity
{
public:
	static void Initialise();
	static void AddSound(const std::string& audioPath, const std::string& audioName, float audioRange);
	static void AddSound(const std::string& audioPath, const std::string& audioName, float audioRange, bool ambient);
	static void PlaySound(const std::string& audioName, Vector3 position);
	static void PlayMusic(const std::string& musicPath, CEntity* attachedEntity);
private:
	static std::map<std::string, AudioEmitterEntity*> audioEmitterMap;
	static AudioEmitterEntity* musicAudioEmitter;
};

