#pragma once

#pragma warning(push)
//Disabled Warnings that reside in external libraries.
#pragma warning( disable : 4505 )
#pragma warning( disable : 26812 )
#include "Cerberus/Dependencies/FMOD/api/core/inc/fmod.hpp"
#include "Cerberus/Dependencies/FMOD/api/core/inc/fmod_errors.h"
#pragma warning(pop)

#include "Cerberus\Core\CEntity.h"
#include "Cerberus/Core/Utility/DebugOutput/Debug.h"
#include "Cerberus/Core/Utility/AssetManager/AssetManager.h"
#include "Cerberus/Core/Utility/Audio/CEmitter.h"
#include "Cerberus\Core\Utility\Vector3.h"

class AudioController
{
public:
	static void Initialize();
	static void Shutdown();

	static CAudio* LoadAudio(const std::string& path);
	static bool PlayAudio(const std::string& path);
	static bool StopAudio(const std::string& path);
	static bool DestroyAudio(const std::string& path);

	static void Update(float deltaTime);

	static std::vector<CEmitter*> GetAllEmittersWithinRange(Vector3 position, bool checkIfPlaying);
	static bool AddEmitter(CEmitter* emitter);
	static bool AddEmitter(CEmitter* emitter, bool ambient);
	static bool RemoveEmitter(CEmitter* emitter);

	static bool AddListener(CTransform* listenerPos);

private:
	static FMOD::System* FMODSystem;
	static std::vector<CEmitter*> emitters;
	static std::vector<CEmitter*> ambientEmitters;
	static CTransform* listenerTransform;
};

