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
	float walkSpeed = 300;
	float walkDrag = 10;
	float timeElapsed = 0;

	void LookAt(Vector3 pos);

	CAnimationSpriteComponent* spriteComponentBody = nullptr;
	CAnimationSpriteComponent* spriteComponentLegs = nullptr;
	CSpriteComponent* spriteComponentShadow = nullptr;

	Vector2 movementVec = { 0,0 };
	XMFLOAT2 movementVel = { 0,0 };
	const float walkAnimationSpeed = 1.3f;

	const float cameraMovementScalar = 100.0f;
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

