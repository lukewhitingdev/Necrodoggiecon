#pragma once
#include "Necrodoggiecon/Game/CInteractable.h"
#include "Necrodoggiecon/Game/weapons.h"
#include "Cerberus/Core/Utility/DebugOutput/Debug.h"
#include "Necrodoggiecon/Game/PlayerCharacter.h"
#include "Cerberus/Core/Utility/IO.h"

template<typename T>
class WeaponPickup : public CInteractable
{
public:
	WeaponPickup();
	virtual ~WeaponPickup();

	virtual void OnInteract() override;

private:
	T* pickup;
};

template<typename T>
inline WeaponPickup<T>::WeaponPickup()
{
	T* weapon = new T();
	Weapon* baseWeapon = dynamic_cast<Weapon*>(weapon);
	if (baseWeapon != nullptr)
	{
		pickup = weapon;

		std::string ext = IO::FindExtension(baseWeapon->GetIconPath());
		if(ext == "dds")
		{
			GetSprite()->LoadTexture(baseWeapon->GetIconPath());
		}
		else
		{
			GetSprite()->LoadTextureWIC(baseWeapon->GetIconPath());
		}
	}
	else
	{
		Debug::LogError("Tried to create a entity with invalid type: %s", typeid(*weapon).name());
		delete weapon;
		return;
	}
};

template<typename T>
inline WeaponPickup<T>::~WeaponPickup()
{
	delete pickup;
	pickup = nullptr;
}

/**
 * Updates the player character's weapon when the player interacts.
 * 
 */
template<typename T>
inline void WeaponPickup<T>::OnInteract()
{
	PlayerCharacter* player = dynamic_cast<PlayerCharacter*>(this->GetLastCollidedObject()->GetParent());

	if (player != nullptr)
	{
		if (this->pickup != nullptr)
		{
			player->EquipWeapon(reinterpret_cast<Weapon*>(new T()));
			this->pickup = nullptr;
			Engine::DestroyEntity(this);
		}
		else
		{
			Debug::LogError("Tried to interact with a weapon pickup that doesnt have one set!.");
			return;
		}
	}
	else
	{
		Debug::LogError("Tried to interact with a weapon when not the player character!.");
		return;
	}
}
