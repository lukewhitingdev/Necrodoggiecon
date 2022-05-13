#pragma once
#include <string>
#include <fstream>

<<<<<<< Updated upstream
#include "Cerberus/Core/CComponent.h"
#include "Cerberus/Core/CEntity.h"
=======
#include "Projectile.h"
#include <Cerberus\Core\CEntity.h>
>>>>>>> Stashed changes
#include "Cerberus\Core\Engine.h"
#include "Cerberus/Core/Utility/DebugOutput/Debug.h"
#include "Cerberus\Core\Utility\Vector3.h"
#include "Cerberus\Dependencies\NlohmannJson\json.hpp"

#define rangeScale 320.0f

using json = nlohmann::json;

enum class USERTYPE
{
	PLAYER,
	AI,
};

class Weapon : public CComponent
{
public:
	Weapon();

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
	USERTYPE GetUserType() { return userType; };

private:
	void CoolDown(float attack_cooldown);


	void HandleMelee(Vector3 actorPos, Vector3 normAttackDir);
	void HandleRanged(Vector3 actorPos, Vector3 normAttackDir);

	CEntity* GetClosestEnemy(Vector3 actorPos);
	CEntity* GetClosestPlayer(Vector3 actorPos);

	std::string type;
	float damage;
	float range;
	float attack_speed;
	float ammo;
	bool unique;

	USERTYPE userType;

protected:
	
};

