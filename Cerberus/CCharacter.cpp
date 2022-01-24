#include "CCharacter.h"

void CCharacter::AddVerticalMovement(int dir, float speed, float deltaTime)
{
	Vector3 pos = GetPosition();
	pos.y += dir * (speed * deltaTime);
	SetPosition(pos);
}

void CCharacter::AddHorizontalMovement(int dir, float speed, float deltaTime)
{
	Vector3 pos = GetPosition();
	pos.x += dir * (speed * deltaTime);
	SetPosition(pos);
}
