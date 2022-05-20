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


class Projectile : public CEntity
{
public:

	Projectile();
	~Projectile();

	void StartUp(Vector3 dir, Vector3 pos, float speed, float lifetime, int type, float dam);
	void DidItHit();
	virtual void Update(float deltaTime) override;

private:
	
	class CSpriteComponent* ProjectileSprite = nullptr;
	float Speed;
	float Lifetime;
	float damage;
	Vector3 Direction;
	Vector3 Position;
	Vector3 initialPosition;

	CAIController* GetClosestEnemy(Vector3 actorPos);
	PlayerCharacter* GetClosestPlayer(Vector3 actorPos);

	USERTYPE2 userType;
	bool hasHit = false;
};

