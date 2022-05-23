#include "CCharacter.h"
#include "Necrodoggiecon\Game\WeaponPickup.h"

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
