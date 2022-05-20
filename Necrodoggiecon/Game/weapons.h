/*****************************************************************//**
 * \file   weapons.h
 * \brief  Base Weapon class for the weapons in the game, this will be inherited by the custom classes of the weapons
 * 
 * \author Ben Brown & Flynn Brooks
 * \date   May 2022
 *********************************************************************/
#pragma once
#include <string>
#include <fstream>

#include "Cerberus/Core/CComponent.h"
#include "Cerberus/Core/CEntity.h"
#include "Cerberus\Core\Engine.h"
#include "Cerberus/Core/Utility/DebugOutput/Debug.h"
#include "Cerberus\Core\Utility\Vector3.h"
#include "Cerberus\Dependencies\NlohmannJson\json.hpp"

#define rangeScale 64.0f

using json = nlohmann::json;

enum class USERTYPE
{
	PLAYER,
	AI,
};

class Weapon : public CComponent
{
public:	
	Weapon(std::string weapon = "Dagger");

	void SetWeapon(std::string weapon);
	virtual void OnFire(Vector3 actorPos, Vector3 attackDir);
	virtual void Update(float deltaTime) override;
	virtual void Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer) override;

	void SetUserType(USERTYPE userType) { this->userType = userType; };

	std::string GetType() { return type; };
	float GetDamage() { return damage; };
	float GetRange() { return range; };
	float GetAttack_Speed() { return attack_speed; };
	float GetAmmo() { return ammo; };
	bool GetUnique() { return unique; };
	bool GetCanFire() { return canFire; };
	void SetCanFire(bool canFire) { this->canFire = canFire; };
	USERTYPE GetUserType() { return userType; };
	std::string GetName() { return name; }
	std::string GetIconPath() { return iconPath; };

	void StartCooldown() { cooldown = attack_speed; };

private:
	void CoolDown(float attack_cooldown);

	void HandleMelee(Vector3 actorPos, Vector3 normAttackDir);
	void HandleRanged();

	CEntity* GetClosestEnemy(Vector3 actorPos, Vector3 damagePos);
	CEntity* GetClosestPlayer(Vector3 actorPos, Vector3 damagePos);

	std::string iconPath;
	std::string type;
	std::string name;
	float damage;
	float range;
	float attack_speed;
	float ammo;
	bool unique;
	bool canFire = true;
	float cooldown;

	USERTYPE userType;

protected:
	
};

