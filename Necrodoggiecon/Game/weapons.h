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

#include "Necrodoggiecon/Projectile.h"
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

/**
 * Base Weapon class inherited by all weapons.
 */
class Weapon : public CComponent
{
public:	
	Weapon(std::string weapon = "Dagger");

	void SetWeapon(int ID);
	void SetWeapon(std::string ID);

	std::string IDToName(int ID);
	int NameToID(std::string Name);

	virtual void OnFire(Vector3 actorPos, Vector3 attackDir);
	virtual void Update(float deltaTime) override;
	virtual void Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer) override;

	void SetUserType(USERTYPE userType) { this->userType = userType; };

	std::string GetType() { return type; };
	std::string GetProjectileIcon() { return projectileIconPath; };
	float GetDamage() { return damage; };
	float GetRange() { return range; };
	float GetAttack_Speed() { return attack_speed; };
	float GetAmmo() { return ammo; };
	void SetAmmo(float amount) { ammo = amount; };
	bool GetUnique() { return unique; };
	bool GetCanFire() { return canFire; };
	void SetCanFire(bool canFire) { this->canFire = canFire; };
	void SetTextureOffset(XMFLOAT2 offset) { textureOffset = offset; };
	XMFLOAT2 GetTextureOffset() { return textureOffset; };
	void SetRenderRect(XMUINT2 rect) { renderRect = rect; };
	XMUINT2 GetRenderRect() { return renderRect; };
	void SetScale(XMFLOAT3 setScale) { scale = setScale; };
	XMFLOAT3 GetScale() { return scale; };
	USERTYPE GetUserType() { return userType; };
	std::string GetName() { return name; }
	std::string GetIconPath() { return iconPath; };

	void StartCooldown() { cooldown = attack_speed; };

private:
	void CoolDown(float attack_cooldown);

	std::string iconPath;
	std::string projectileIconPath;
	std::string type;
	std::string name;
	float damage;
	float range;
	float attack_speed;
	float ammo;
	bool unique;
	bool canFire = true;
	float cooldown;

	XMFLOAT2 textureOffset = XMFLOAT2(0.0, 0.0);
	XMUINT2 renderRect = XMUINT2(64, 64);
	XMFLOAT3 scale = XMFLOAT3(1.0, 1.0, 1.0);

	USERTYPE userType;

protected:
	std::string pickupType;

};

