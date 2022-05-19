#pragma once
#include <Necrodoggiecon\Game\CCharacter.h>
#include <Cerberus\Core\Environment\IInputable.h>
#include "Cerberus/Core/Components/CAudioEmitterComponent.h"

#include "weapons.h"

class CDroppedItem;
class CEquippedItem;

class PlayerCharacter : public CCharacter, public IInputable
{
protected:
	float speed = 200;
	float timeElapsed = 0;

	void LookAt(Vector3 pos);

	CAnimationSpriteComponent* spriteComponentBody = nullptr;
	CAnimationSpriteComponent* spriteComponentLegs = nullptr;

	XMFLOAT2 movementVec = { 0,0 };
public:
	PlayerCharacter();

	void PressedHorizontal(int dir, float deltaTime) override;
	void PressedVertical(int dir, float deltaTime) override;
	void PressedInteract() override;
	void PressedDrop() override;
	void Attack() override;
	virtual void Update(float deltaTime) override;

	CDroppedItem* droppedItem = nullptr;
	CEquippedItem* equippedItem = nullptr;

	Weapon* weapon = nullptr;
	class CCameraComponent* camera = nullptr;
	CAudioEmitterComponent* loadNoise;
};

