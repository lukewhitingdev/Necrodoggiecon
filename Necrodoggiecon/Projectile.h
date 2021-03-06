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

class CAudioEmitterComponent;
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

	void StartUp(Vector3 dir, Vector3 pos, float damage, float speed, float lifetime, int type, const std::string &projectile_name, const std::string& hitAudioPath);
	void DidItHit();
	virtual void Update(float deltaTime) override;

	void SetLifetime(float life) { Lifetime = life; }
	float GetLifetime() { return Lifetime; };
	Vector3 GetPosition() { return Position; };
	void SetPosition(Vector3 newPosition) { Position = newPosition; };
	Vector3 GetDirection() { return Direction; };
	float GetSpeed() { return Speed; };
	void SetSpeed(float speed) { Speed = speed; };
	void SetVelocity() { velocity = Direction * Speed; };

	USERTYPE2 GetUserType() { return userType; };
	class CSpriteComponent* ProjectileSprite = nullptr;

	bool hasHit = false;
private:
	float Damage;

	float Speed;
	float Lifetime;
	float damage;
	Vector3 velocity = { 0.0f, 0.0f, 0.0f };
	Vector3 acceleration = { 0.0f, 0.0f, 0.0f };
	Vector3 Direction;
	Vector3 Position;
	Vector3 initialPosition;
	std::string Projectile_Name;
	std::string onHitAudioPath;


	CAIController* GetClosestEnemy(Vector3 actorPos);
	PlayerCharacter* GetClosestPlayer(Vector3 actorPos);
	CAIController* GetClosestEnemy(Vector3 actorPos, float ranged);
	USERTYPE2 userType;

	virtual void HasCollided(CollisionComponent* collidedObject)
	{
		if (collidedObject->GetName() == "Wall")
		{
			hasHit = true;
		}
	}
};

