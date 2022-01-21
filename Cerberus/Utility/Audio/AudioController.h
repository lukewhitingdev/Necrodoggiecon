#pragma once
#include "Dependencies/FMOD/api/core/inc/fmod.hpp"
#include "Dependencies/FMOD/api/core/inc/fmod_errors.h"
#include "Utility/DebugOutput/Debug.h"
#include "Utility/AssetManager/AssetManager.h"

class AudioController
{
public:
	static void Initialize();
	static void Shutdown();

	static bool LoadAudio(std::string path, bool looping);
	static bool PlayAudio(std::string path);
	static bool StopAudio(std::string path);
	static bool DestroyAudio(std::string path);

private:
	static FMOD::System* FMODSystem;
};

