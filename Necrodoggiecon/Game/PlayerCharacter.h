#pragma once
#include <Necrodoggiecon\Game\CCharacter.h>
#include <Cerberus\Core\Environment\IInputable.h>
#include "Cerberus/Core/Components/CAudioEmitterComponent.h"
#include "Cerberus/Core/Utility/DebugOutput/Debug.h"

#include "weapons.h"
#include <Necrodoggiecon/Weapons/Melee/Dagger.h>
#include <Necrodoggiecon/Weapons/Melee/Rapier.h>
#include <Necrodoggiecon/Weapons/Melee/Longsword.h>

class PlayerController;

class PlayerCharacter : public CCharacter, public IInputable, public IUsePickup
{
protected:
	float walkSpeed = 300;
	float walkDrag = 10;
	float timeElapsed = 0;

	void LookAt(Vector3 pos);

	CAnimationSpriteComponent* spriteComponentBody = nullptr;
	CAnimationSpriteComponent* spriteComponentLegs = nullptr;
	CSpriteComponent* spriteComponentShadow = nullptr;
	CSpriteComponent* spriteComponentShield = nullptr;
	std::vector<PlayerController*> playersController = Engine::GetEntityOfType<PlayerController>();

	Vector2 movementVec = { 0,0 };
	XMFLOAT2 movementVel = { 0,0 };
	const float walkAnimationSpeed = 1.3f;

	float pickupTimer;
	bool pickupActive;
	float pickupActiveTime;
	bool visible;
	std::function<void()> pickupTimerCallback;
	void InvisibilityCallback();
	void PickupTimer(float deltaTime);

	void ToggleVisibility(bool isVisible);
	void GiveShield();
	const float cameraMovementScalar = 100.0f;
public:
	PlayerCharacter();

	void PressedHorizontal(int dir, float deltaTime) override;
	void PressedVertical(int dir, float deltaTime) override;
	void PressedInteract() override;
	void PressedDrop() override;
	void Attack() override;
	void PressedUse() override;

	Weapon* weapon = nullptr;
	class CCameraComponent* camera = nullptr;
	CAudioEmitterComponent* loadNoise;

	void UsePickup(const std::string& pickupToUse, float activeTime) override;
	bool GetVisible() { return visible; }

	virtual void Update(float deltaTime) override;
	void EquipWeapon(Weapon* weapon);
	void UpdateWeaponSprite();

	void ApplyDamage(float damage);

	class CCameraComponent* camera = nullptr;
	CAudioEmitterComponent* loadNoise = nullptr;
	CSpriteComponent* weaponSprite = nullptr;

private:
	void ResolveMovement(const float& deltaTime);
	void AimAtMouse(const Vector3& mousePos);
};

