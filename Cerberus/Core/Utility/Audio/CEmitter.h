/*****************************************************************//**
 * \file   CEmitter.h
 * \brief  A helper class to help encapsulate emitters that can be used by the audio system. Different from the audio emitter component.
 * 
 * \author Luke Whiting
 * \date   Jan 2022
 *********************************************************************/
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