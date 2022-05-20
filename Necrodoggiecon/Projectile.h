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

	void StartUp(Vector3 dir, Vector3 pos, float speed, float lifetime, std::string projectile_name);
	void DidItHit();
	virtual void Update(float deltaTime) override;

private:
	
	class CSpriteComponent* ProjectileSprite = nullptr;
	float Speed;
	float Lifetime;
	Vector3 Direction;
	Vector3 Position;
	std::string Projectile_Name;

	CEntity* GetClosestEnemy(Vector3 actorPos);
	CEntity* GetClosestEnemy(Vector3 actorPos, float ranged);
	CEntity* GetClosestPlayer(Vector3 actorPos);

	USERTYPE2 userType;
};

