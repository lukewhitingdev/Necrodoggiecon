#pragma once
#include <Necrodoggiecon\Game\CCharacter.h>
#include <Cerberus\Core\Environment\IInputable.h>
#include "Cerberus/Core/Components/CAudioEmitterComponent.h"
#include "Cerberus/Core/Utility/DebugOutput/Debug.h"

#include "weapons.h"
#include <Necrodoggiecon/Weapons/Melee/Dagger.h>
#include <Necrodoggiecon/Weapons/Melee/Rapier.h>
#include <Necrodoggiecon/Weapons/Melee/Longsword.h>

class CDroppedItem;
class CEquippedItem;

class PlayerCharacter : public CCharacter, public IInputable
{
protected:
	float speed = 200;
	float timeElapsed = 0;

	void LookAt(Vector3 pos);
public:
	PlayerCharacter();

	void PressedHorizontal(int dir, float deltaTime) override;
	void PressedVertical(int dir, float deltaTime) override;
	void PressedInteract() override;
	void PressedDrop() override;
	void Attack() override;
	virtual void Update(float deltaTime) override;
	void EquipWeapon(Weapon* weapon);
	void UpdateWeaponSprite();

	CDroppedItem* droppedItem = nullptr;
	CEquippedItem* equippedItem = nullptr;
	class CCameraComponent* camera = nullptr;
	CAudioEmitterComponent* loadNoise = nullptr;
	CSpriteComponent* weaponSprite = nullptr;
};

