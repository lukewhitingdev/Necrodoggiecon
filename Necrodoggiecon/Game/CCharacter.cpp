#include "CCharacter.h"

CCharacter::CCharacter()
{
}

CCharacter::~CCharacter()
{
}

void CCharacter::SetHealth(float heal)
{
	health = heal;
}

float CCharacter::GetHealth()
{
	return health;
}

void CCharacter::AddVerticalMovement(int dir, float speed, float deltaTime)
{
	Vector3 pos = GetPosition();
	pos.x += vel.x * deltaTime;
	pos.y += vel.y * deltaTime;
	SetPosition(pos);
}
