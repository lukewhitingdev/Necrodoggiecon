#pragma once
#include "Engine.h"
#include "CEntity.h"
#include "CSpriteComponent.h"
#include "CAudioEmitterComponent.h"
#include <stdio.h>

class CAICharacter : public CEntity
{
	float timeElapsed = 0;
public:
	class CSpriteComponent* viewSprite = nullptr;
	CAudioEmitterComponent* audioEmitter = nullptr;
	CAICharacter();
	virtual void Update(float deltaTime) override;
	virtual ~CAICharacter();
};
