#pragma once
#include <CSpriteComponent.h>
#include <CEntity.h>
#include "CAudioListenerComponent.h"

class CCharacter : public CEntity
{
private:
protected:
	CSpriteComponent* spriteComponent = nullptr;
	CAudioListenerComponent* listenerComponent = nullptr;

	virtual void OnTakeDamage(float damageAmount, CEntity* damageCauser) {};

	void AddVerticalMovement(int dir, float speed, float deltaTime);
	void AddHorizontalMovement(int dir, float speed, float deltaTime);
public:
	void ApplyDamage(int damageAmount, CEntity* damageCauser) { OnTakeDamage(damageAmount, damageCauser); }

};

