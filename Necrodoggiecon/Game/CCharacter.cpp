#include "CCharacter.h"
#include "Necrodoggiecon\Game\WeaponPickup.h"

/*****************************************************************//**
 * \file   CCharacter.cpp
 * \brief  Base class for Characters
 *
 * \author Cathan Bertram
 * \date   May 2022
 *********************************************************************/

CCharacter::CCharacter()
{
}

CCharacter::~CCharacter()
{
	if(weaponComponent != nullptr)
	{
		WeaponPickup<Weapon>* pickup = Engine::CreateEntity<WeaponPickup<Weapon>>();
		pickup->SetWeapon(weaponComponent->GetCurrentWeapon());
		pickup->SetPosition(this->GetPosition());
	}
}
/*
* Function to add vertical movement to the character
* dir is the direction on the y axis that the character will move
* speed is how fast to move the character
* deltaTime is used to ensure the character will move at a consistent speed that is not dependent on frame rate
*/
void CCharacter::AddVerticalMovement(int dir, float speed, float deltaTime){}


/**
* Function to add vertical movement to the character
* dir is the direction on the y axis that the character will move
* speed is how fast to move the character
* deltaTime is used to ensure the character will move at a consistent speed that is not dependent on frame rate
*/
void CCharacter::AddHorizontalMovement(int dir, float speed, float deltaTime){}

void CCharacter::SetHealth(float heal)
{
	health = heal;
}

float CCharacter::GetHealth()
{
	return health;
}

void CCharacter::AddMovement(XMFLOAT2 vel, float deltaTime)
{
	Vector3 pos = GetPosition();
	pos.x += vel.x * deltaTime;
	pos.y += vel.y * deltaTime;
	SetPosition(pos);
}
