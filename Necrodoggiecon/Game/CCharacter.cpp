#include "CCharacter.h"

CCharacter::CCharacter()
{
}

CCharacter::~CCharacter()
{
}

void CCharacter::AddMovement(XMFLOAT2 vel, float deltaTime)
{
	Vector3 pos = GetPosition();
	pos.x += vel.x * deltaTime;
	pos.y += vel.y * deltaTime;
	SetPosition(pos);
}
