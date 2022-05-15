#include "CCharacter.h"

CCharacter::CCharacter()
{
	//rigidbody = AddComponent<CRigidBodyComponent>();
}

CCharacter::~CCharacter()
{
}

void CCharacter::AddVerticalMovement(int dir, float speed, float deltaTime)
{
	if(!rigidbody)
	{
		Vector3 pos = GetPosition();
		pos.y += dir * (speed * deltaTime);
		SetPosition(pos);
	}
	else
	{
		rigidbody->SetVelocity(Vector3(rigidbody->GetVelocity().x, (dir > 0) ? speed : -speed, rigidbody->GetVelocity().z));
	}
}

void CCharacter::AddHorizontalMovement(int dir, float speed, float deltaTime)
{
	if (!rigidbody)
	{
		Vector3 pos = GetPosition();
		pos.x += dir * (speed * deltaTime);
		SetPosition(pos);
	}
	else
	{
		rigidbody->SetVelocity(Vector3((dir > 0) ? speed : -speed, rigidbody->GetVelocity().y, rigidbody->GetVelocity().z));
	}
}
