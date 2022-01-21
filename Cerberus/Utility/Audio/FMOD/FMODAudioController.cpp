#include "FMODAudioController.h"
FMOD::System* FMODAudioController::FMODSystem;

void FMODAudioController::Initialize()
{
	if (FMOD::System_Create(&FMODSystem) != FMOD_OK)
		throw;

	FMODSystem->init(512, FMOD_INIT_NORMAL, 0);
}

void FMODAudioController::Shutdown()
{
	FMODSystem->release();
}

void FMODAudioController::LoadAudio(std::string path, bool looping)
{
	FMOD::Sound* sound;
	FMOD::Channel* channel;

	FMOD_RESULT result;

	std::string fullPath = SOLUTION_DIR + path;

	if ((result = FMODSystem->createSound(fullPath.c_str(), FMOD_2D, nullptr, &sound)) != FMOD_OK)
	{
		Debug::LogError("FMOD Error[%d]: %s ", result, FMOD_ErrorString(result));
	}

	if ((result = FMODSystem->playSound(sound, nullptr, false, &channel)) != FMOD_OK)
	{
		Debug::LogError("FMOD Error[%d]: %s ", result, FMOD_ErrorString(result));
	}
}
