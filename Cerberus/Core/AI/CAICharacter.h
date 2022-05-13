#pragma once
#include "Cerberus\Core\Engine.h"
#include "Cerberus\Core\CEntity.h"
#include "Cerberus\Core\Components\CSpriteComponent.h"
#include <stdio.h>

class CAICharacter : public CEntity
{
	float timeElapsed = 0;
public:
	class CSpriteComponent* viewSprite = nullptr;
	CAICharacter();
	virtual void Update(float deltaTime) override;
	virtual ~CAICharacter();
};
