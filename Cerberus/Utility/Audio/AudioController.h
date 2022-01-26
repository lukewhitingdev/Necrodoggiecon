#pragma once
#include "Dependencies/FMOD/api/core/inc/fmod.hpp"
#include "Dependencies/FMOD/api/core/inc/fmod_errors.h"
#include "Utility/DebugOutput/Debug.h"
#include "Utility/AssetManager/AssetManager.h"
#include "Utility/Audio/CEmitter.h"
#include "Vector3.h"

class AudioController
{
public:
	static void Initialize();
	static void Shutdown();

	static CAudio* LoadAudio(std::string path);
	static bool PlayAudio(std::string path);
	static bool StopAudio(std::string path);
	static bool DestroyAudio(std::string path);

	static void Update(Vector3 listenerPos, float deltaTime);

	static std::vector<CEmitter*> GetAllEmittersWithinRange(Vector3 position);
	static void AddEmitter(CEmitter* emitter);
	static void RemoveEmitter(CEmitter* emitter);

private:
	static FMOD::System* FMODSystem;
	static std::vector<CEmitter*> emitters;
};

