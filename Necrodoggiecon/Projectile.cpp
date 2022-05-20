#include "Projectile.h"
#include <Cerberus\Core\AI\CAIController.h>
#include <Necrodoggiecon\Game\PlayerCharacter.h>

Projectile::Projectile()
{
	ProjectileSprite = AddComponent<CSpriteComponent>();
	ProjectileSprite->LoadTextureWIC("Resources/weapons/Arrow.png");
	ProjectileSprite->SetRenderRect(XMUINT2(64, 64));
	ProjectileSprite->SetSpriteSize(XMUINT2(96, 96));

}

Projectile::~Projectile()
{
	//RemoveComponent(colComponent);
}

void Projectile::Update(float deltaTime)
{
	if (initialPosition.DistanceTo(ProjectileSprite->GetPosition()) < Lifetime)
	{
		DidItHit();
		Position += Direction * Speed;
		ProjectileSprite->SetPosition(Position);
	}
	else
	{
		Engine::DestroyEntity(this);
	}
}

void Projectile::DidItHit()
{
	Vector3 damagePos = Position + Direction * 1;

	if (userType == USERTYPE2::AI)
	{
		PlayerCharacter* target = GetClosestPlayer(damagePos);
		if (target != nullptr)
			target->ApplyDamage(1.0f, GetClosestEnemy(damagePos));
	}
	else if (userType == USERTYPE2::PLAYER)
	{
		CAIController* target = GetClosestEnemy(damagePos);
		if (target != nullptr)
			target->ApplyDamage(1.0f, GetClosestPlayer(damagePos));
	}

}

void Projectile::StartUp(Vector3 dir, Vector3 pos, float speed, float lifetime, int type)
{
	Direction = dir;
	ProjectileSprite->SetPosition(pos);
	Position = pos;
	Speed = speed;
	Lifetime = lifetime;
	initialPosition = pos;

	userType = (USERTYPE2)type;

	Vector3 up = { 0.0f, 1.0f, 0.0f };

	if (dir == Vector3(0, 0, 0))
		return;

	float dot = up.Dot(dir);
	float det = up.x * dir.y - up.y * dir.x;

	ProjectileSprite->SetRotation(atan2f(det, dot));
}




CAIController* Projectile::GetClosestEnemy(Vector3 actorPos)
{
	std::vector<CAIController*> enemies = Engine::GetEntityOfType<CAIController>();

	if (enemies.size() == 0) //No enemies
		return nullptr;

	CAIController* closestEnemy = nullptr;

	//Check each enemy
	for (CAIController* enemy : enemies)
	{

		if (actorPos.DistanceTo(enemy->GetPosition()) > 50)
			continue;

		if (closestEnemy == nullptr)
			closestEnemy = enemy;
		else
		{
			if (actorPos.DistanceTo(enemy->GetPosition()) < actorPos.DistanceTo(closestEnemy->GetPosition()))
				closestEnemy = enemy;
		}
	}

	return closestEnemy;
}

PlayerCharacter* Projectile::GetClosestPlayer(Vector3 actorPos)
{
	std::vector<PlayerCharacter*> players = Engine::GetEntityOfType<PlayerCharacter>();

	if (players.size() == 0) //No players
		return nullptr;

	PlayerCharacter* closestPlayer = nullptr;

	//Check each player
	for (PlayerCharacter* player : players)
	{

		if (actorPos.DistanceTo(player->GetPosition()) > 50)
			continue;

		if (closestPlayer == nullptr)
			closestPlayer = player;
		else
		{
			if (actorPos.DistanceTo(player->GetPosition()) < actorPos.DistanceTo(closestPlayer->GetPosition()))
				closestPlayer = player;
		}
	}

	return closestPlayer;
}