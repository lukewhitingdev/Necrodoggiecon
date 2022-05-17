#include "Projectile.h"
#include <Necrodoggiecon\Game\AI\CAIController.h>

Projectile::Projectile()
{
	ProjectileSprite = AddComponent<CSpriteComponent>();
	ProjectileSprite->LoadTextureWIC("Resources/weapons/Arrow.png");
	ProjectileSprite->SetRenderRect(XMUINT2(64, 64));
	ProjectileSprite->SetSpriteSize(XMUINT2(96, 96));

}

Projectile::~Projectile()
{

}

void Projectile::Update(float deltaTime)
{
	if (Lifetime > 0)
	{
		DidItHit();
		Position += Direction * Speed;
		ProjectileSprite->SetPosition(Position);
		Lifetime--;
	}
}

void Projectile::DidItHit()
{

}

void Projectile::StartUp(Vector3 dir, Vector3 pos, float speed, float lifetime)
{
	Direction = dir;
	ProjectileSprite->SetPosition(pos);
	Position = pos;
	Speed = speed;
	Lifetime = lifetime;

	Vector3 up = { 0.0f, 1.0f, 0.0f };

	if (dir == Vector3(0, 0, 0))
		return;

	float dot = up.Dot(dir);
	float det = up.x * dir.y - up.y * dir.x;

	ProjectileSprite->SetRotation(atan2f(det, dot));
}