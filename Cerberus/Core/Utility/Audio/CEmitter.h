#pragma once
#include "Utility/Vector3.h"
#include "Utility/Audio/CAudio.h"

class CEmitter
{
public:
	Vector3 position;
	float range = 1000;
	CAudio* audio;
};