#pragma once
#include <Cerberus\Core\Components\CAnimationSpriteComponent.h>
#include <Cerberus\Core\CEntity.h>

class Projectile : public CEntity
{
public:

	Projectile();
	~Projectile();

	void StartUp(Vector3 dir, Vector3 pos, float speed, float lifetime);
	void DidItHit();
	virtual void Update(float deltaTime) override;

private:
	void RotationOfArrow();
	class CSpriteComponent* ProjectileSprite = nullptr;
	float Speed;
	float Lifetime;
	Vector3 Direction;
	Vector3 Position;
};

