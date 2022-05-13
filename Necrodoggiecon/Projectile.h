#pragma once
#include <Cerberus\Core\Components\CSpriteComponent.h>
#include <Cerberus\Core\CEntity.h>
#include "Necrodoggiecon/Game/weapons.h"

class Projectile : public CEntity
{
public:
	float timeElapsed = 0;
	CSpriteComponent* spriteComponent = nullptr;
	Projectile();
	virtual void Update(float deltaTime) override;
private:

};

