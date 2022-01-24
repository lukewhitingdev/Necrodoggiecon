#pragma once
#include "Vector3.h"
#include "Utility/Audio/CAudio.h"

class CEmitter
{
public:
	Vector3 position;
	float range;
	CAudio* audio;
};