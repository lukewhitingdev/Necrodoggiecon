#pragma once
#include <Necrodoggiecon\Game\CCharacter.h>
#include <Cerberus\Core\Environment\IInputable.h>
#include "Cerberus/Core/Components/CAudioEmitterComponent.h"
#include "Game/IUsePickup.h"
#include "weapons.h"

class CDroppedItem;
class CEquippedItem;
struct PickupItemData;

class PlayerCharacter : public CCharacter, public IInputable, public IUsePickup
{
protected:
	float speed = 200;
	float timeElapsed = 0;

	void LookAt(Vector3 pos);

	CAnimationSpriteComponent* spriteComponentBody = nullptr;
	CAnimationSpriteComponent* spriteComponentLegs = nullptr;
	CSpriteComponent* spriteComponentShadow = nullptr;

	XMFLOAT2 movementVec = { 0,0 };
	const float walkAnimationSpeed = 1.3f;

	float pickupTimer;
	bool pickupActive;
	float pickupActiveTime;
	bool visible;
	std::function<void()> pickupTimerCallback;
	void InvisibilityCallback();
	void PickupTimer(float deltaTime);

	void ToggleVisibility(bool isVisible);
public:
	PlayerCharacter();

	void PressedHorizontal(int dir, float deltaTime) override;
	void PressedVertical(int dir, float deltaTime) override;
	void PressedInteract() override;
	void PressedDrop() override;
	void Attack() override;
	void PressedUse() override;

	virtual void Update(float deltaTime) override;

	Weapon* weapon = nullptr;
	class CCameraComponent* camera = nullptr;
	CAudioEmitterComponent* loadNoise;

	void UsePickup(const std::string& pickupToUse, float activeTime) override;
	bool GetVisible() { return visible; }

};

