#pragma once
#include "Cerberus\Core\Utility\Vector3.h"
#include "Cerberus/Core/Utility/Audio/CAudio.h"

class CEmitter
{
public:
	Vector3 position;
	float range = 1000;
	CAudio* audio;
};