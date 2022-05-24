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

	void SetWeapon(T* weapon);

private:

	void UpdateWeaponSprite(Weapon* weapon);

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
		UpdateWeaponSprite(weapon);
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
			player->EquipWeapon(reinterpret_cast<Weapon*>(this->pickup));
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

/**
 * Sets the weapon of the pickup.
 * 
 * \param weapon weapon that the pickup will be set to.
 */
template<typename T>
inline void WeaponPickup<T>::SetWeapon(T* weapon)
{
	Weapon* baseWeapon = dynamic_cast<Weapon*>(weapon);
	if (baseWeapon != nullptr)
	{
		pickup = weapon;
		UpdateWeaponSprite(baseWeapon);
	}
	else
	{
		Debug::LogError("Tried to set weapon on pickup to a type that isnt a weapon. Type: %s", typeid(*weapon).name());
		return;
	}
}

/**
 * Updates the weapon sprite to the sprite of the argument.
 * 
 * \param weapon weapon to change the current sprite to.
 */
template<typename T>
inline void WeaponPickup<T>::UpdateWeaponSprite(Weapon* weapon)
{
	std::string ext = IO::FindExtension(weapon->GetIconPath());
	CSpriteComponent* sprite = this->GetSprite();
	if (ext == "dds")
	{
		sprite->LoadTexture(weapon->GetIconPath());
		sprite->SetTextureOffset(weapon->GetTextureOffset());
		sprite->SetRenderRect(weapon->GetRenderRect());
		sprite->SetScale(weapon->GetScale());
	}
	else
	{
		sprite->LoadTextureWIC(weapon->GetIconPath());
		sprite->SetTextureOffset(weapon->GetTextureOffset());
		sprite->SetRenderRect(weapon->GetRenderRect());
		sprite->SetScale(weapon->GetScale());
	}
}
