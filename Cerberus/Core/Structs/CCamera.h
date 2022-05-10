#pragma once
#include "Cerberus\Core\Engine.h"
#include "Cerberus/Core/CEntity.h"

class CCamera : public CEntity
{
public:
	CCamera() {};
	virtual void Update(float deltaTime) {};
};
