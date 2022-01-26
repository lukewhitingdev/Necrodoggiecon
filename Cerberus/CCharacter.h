#pragma once
#include <CSpriteComponent.h>
#include <CEntity.h>

class CCharacter : public CEntity
{
private:
protected:
	CSpriteComponent* spriteComponent = nullptr;

	virtual void OnTakeDamage(float damageAmount, CEntity* damageCauser) {};

	void AddVerticalMovement(int dir, float speed, float deltaTime);
	void AddHorizontalMovement(int dir, float speed, float deltaTime);
public:
	void ApplyDamage(float damageAmount, CEntity* damageCauser) { OnTakeDamage(damageAmount, damageCauser); }

	virtual void Update(float deltaTime) {};

};

