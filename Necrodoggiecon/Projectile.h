/*****************************************************************//**
 * \file   Projectile.h
 * \brief  Header containing all the functions and variables needed for the Projectile.
 * 
 * \author Flynn Brooks
 * \date   May 2022
 *********************************************************************/

#pragma once
#include <Cerberus\Core\Components\CAnimationSpriteComponent.h>
#include <Cerberus\Core\CEntity.h>
class CAIController;
class PlayerCharacter;

enum class USERTYPE2
{
	PLAYER,
	AI,
};

/**
 * Projectile class for the Projectile.
 */
class Projectile : public CEntity
{
public:

	Projectile();
	~Projectile();

	void StartUp(Vector3 dir, Vector3 pos, float speed, float lifetime, int type, std::string projectile_name);
	void DidItHit();
	virtual void Update(float deltaTime) override;

private:
	
	class CSpriteComponent* ProjectileSprite = nullptr;
	float Speed;
	float Lifetime;
	Vector3 Direction;
	Vector3 Position;
	Vector3 initialPosition;
	std::string Projectile_Name;

	CAIController* GetClosestEnemy(Vector3 actorPos);
	PlayerCharacter* GetClosestPlayer(Vector3 actorPos);
	CAIController* GetClosestEnemy(Vector3 actorPos, float ranged);

	USERTYPE2 userType;
};

