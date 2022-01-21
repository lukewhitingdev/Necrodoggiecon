#pragma once
#include "Dependencies/FMOD/api/core/inc/fmod.hpp"
#include "Dependencies/FMOD/api/core/inc/fmod_errors.h"
#include "Utility/DebugOutput/Debug.h"

class FMODAudioController
{

public:
	static void Initialize();
	static void Shutdown();

	static void LoadAudio(std::string path, bool looping);
	static void PlayAudio(std::string path);
	static void StopAudio(std::string path);
	static void DestroyAudio(std::string path);

private:
	static FMOD::System* FMODSystem;
};

