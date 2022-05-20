#pragma once

#pragma warning(push)
//Disabled Warnings that reside in external libraries.
#pragma warning( disable : 4505 )
#pragma warning( disable : 26812 )
#include "Cerberus/Dependencies/FMOD/api/core/inc/fmod.hpp"
#include "Cerberus/Dependencies/FMOD/api/core/inc/fmod_errors.h"
#pragma warning(pop)


#include "Cerberus/Core/Utility/DebugOutput/Debug.h"
#include "Cerberus/Core/Utility/AssetManager/AssetManager.h"
#include "Cerberus/Core/Utility/Audio/CEmitter.h"
#include "Cerberus\Core\Utility\Vector3.h"

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

	static std::vector<CEmitter*> GetAllEmittersWithinRange(Vector3 position, bool checkIfPlaying);
	static void AddEmitter(CEmitter* emitter);
	static void RemoveEmitter(CEmitter* emitter);

private:
	static FMOD::System* FMODSystem;
	static std::vector<CEmitter*> emitters;
};

