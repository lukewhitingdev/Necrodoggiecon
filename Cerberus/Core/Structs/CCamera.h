/*****************************************************************//**
 * \file   CCamera.h
 * \brief  Class for storing all camera information needed for rendering.
 * 
 * \author Arrien Bidmead
 * \date   January 2022
 *********************************************************************/

#pragma once
#include "Cerberus\Core\Engine.h"
#include "Cerberus/Core/CEntity.h"

class CCamera : public CEntity
{
public:
	CCamera() {};
	virtual void Update(float deltaTime) {};
};
