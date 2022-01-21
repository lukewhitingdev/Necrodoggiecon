#pragma once
#include "Dependencies/FMOD/api/core/inc/fmod.hpp"
#include "Dependencies/FMOD/api/core/inc/fmod_errors.h"
#include "Utility/DebugOutput/Debug.h"
#include "Utility/AssetManager/AssetManager.h"
#include "Vector3.h"

class AudioController
{
public:
	static void Initialize();
	static void Shutdown();

	static bool LoadAudio(std::string path, bool worldSpace);
	static bool PlayAudio(std::string path);
	static bool StopAudio(std::string path);
	static bool DestroyAudio(std::string path);

	static void Update(Vector3 listenerPos, float deltaTime);

private:
	static FMOD::System* FMODSystem;
};

