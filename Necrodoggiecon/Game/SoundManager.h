#pragma once
#include "Cerberus\Core\CEntity.h"
#include <Game/AudioEmitterEntity.h>

class SoundManager :  public CEntity
{
public:
	static void Initialise();
	static void AddSound(const std::string& audioPath, const std::string& audioName, float audioRange);
	static void PlaySound(const std::string& audioName, Vector3 position);
private:
	static std::map<std::string, AudioEmitterEntity*> audioEmitterMap;
};

