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
		Lifetime-2;
	}
}

void Projectile::DidItHit()
{
	Vector3 damagePos = Position + Direction * 1;

	if (userType == USERTYPE2::AI)
	{
		CEntity* target = GetClosestPlayer(damagePos);
		if (target != nullptr)
			Engine::DestroyEntity(target);
	}
	else if (userType == USERTYPE2::PLAYER)
	{
		CEntity* target = GetClosestEnemy(damagePos);
		if (target != nullptr)
			Engine::DestroyEntity(target);
	}

}

void Projectile::StartUp(Vector3 dir, Vector3 pos, float speed, float lifetime, std::string projectile_name)
{
	Direction = dir;
	ProjectileSprite->SetPosition(pos);
	Position = pos;
	Speed = speed;
	Lifetime = lifetime;
	Name = projectile_name;

	Vector3 up = { 0.0f, 1.0f, 0.0f };

	if (dir == Vector3(0, 0, 0))
		return;

	float dot = up.Dot(dir);
	float det = up.x * dir.y - up.y * dir.x;

	ProjectileSprite->SetRotation(atan2f(det, dot));
}




CEntity* Projectile::GetClosestEnemy(Vector3 actorPos)
{
	std::vector<CAIController*> enemies = Engine::GetEntityOfType<CAIController>();

	if (enemies.size() == 0) //No enemies
		return nullptr;

	CAIController* closestEnemy = nullptr;

	//Check each enemy
	for (CAIController* enemy : enemies)
	{

		if (actorPos.DistanceTo(enemy->GetPosition()) > 50)
			break;

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

CEntity* Projectile::GetClosestPlayer(Vector3 actorPos)
{
	std::vector<PlayerCharacter*> players = Engine::GetEntityOfType<PlayerCharacter>();

	if (players.size() == 0) //No players
		return nullptr;

	PlayerCharacter* closestPlayer = nullptr;

	//Check each player
	for (PlayerCharacter* player : players)
	{

		if (actorPos.DistanceTo(player->GetPosition()) > 50)
			break;

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