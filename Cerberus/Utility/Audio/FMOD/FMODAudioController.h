#pragma once
#include "Dependencies/FMOD/api/core/inc/fmod.hpp"
#include "Utility/DebugOutput/Debug.h"


class FMODAudioController
{
	static FMOD::System* FMODSystem;

	static void Initialize();
};

