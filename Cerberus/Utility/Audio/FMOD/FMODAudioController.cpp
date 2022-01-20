#include "FMODAudioController.h"
FMOD::System* FMODAudioController::FMODSystem;

void FMODAudioController::Initialize()
{
	if (FMOD::System_Create(&FMODSystem) != FMOD_OK)
		throw;

	FMODSystem->init(512, FMOD_INIT_NORMAL, 0);
}
