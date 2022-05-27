#include "Game/PlayerCharacter.h"
#include "Cerberus/Core/Utility/Math/Math.h"
#include "Cerberus\Core\Components\CCameraComponent.h"
#include "Cerberus/Core/Utility/IO.h"
#include "Necrodoggiecon/Game/PlayerController.h"
#include "Cerberus/Core/Utility/CameraManager/CameraManager.h"
#include<Necrodoggiecon/Weapons/Ranged/Crossbow.h>
#include "Necrodoggiecon/Weapons/Pickup/ShieldScroll.h"
#include "Necrodoggiecon/Weapons/Pickup/InvisibilityScroll.h"
#include <Necrodoggiecon/Weapons/Ranged/MagicMissile.h>
#include "weaponUI.h"
#include "CursorEntity.h"
#include <Game/SoundManager.h>
#include "Cerberus/Core/Utility/CUIManager.h"
#include "Necrodoggiecon/DeathMenu.h"

PlayerCharacter::PlayerCharacter()
{
	isPlayer = true;

	if(!AudioController::AddListener(static_cast<CTransform*>(this)))
	{
		Debug::LogError("An error occured whilst trying to add the player as a listener for the audio controller. See error above.");
	}

	SetShouldMove(true);

	spriteComponentBody = AddComponent<CAnimationSpriteComponent>(NAME_OF(spriteComponentBody));
	spriteComponentBody->LoadTextureWIC("Resources/Game/Characters/JonathanWicke-sheet.png");
	spriteComponentBody->SetSpriteSize(XMUINT2(64, 64));
	spriteComponentBody->SetRenderRect(XMUINT2(44, 44));
	spriteComponentBody->SetAnimationRectSize(XMUINT2(2, 1));
	spriteComponentBody->SetAnimationSpeed(2 * walkAnimationSpeed);
	spriteComponentBody->SetPlaying(false, false);
	spriteComponentBody->SetUseTranslucency(true);
	originalSpriteTint = spriteComponentBody->GetTint();

	spriteComponentLegs = AddComponent<CAnimationSpriteComponent>(NAME_OF(spriteComponentLegs));
	spriteComponentLegs->LoadTextureWIC("Resources/Game/Characters/legsSpriteSheet.png");
	spriteComponentLegs->SetPosition(XMFLOAT3(0, 0, 1));
	spriteComponentLegs->SetScale(XMFLOAT3(2, 1.5, 1.5));
	spriteComponentLegs->SetRenderRect(XMUINT2(29, 22));
	spriteComponentLegs->SetSpriteSize(XMUINT2(29, 22));
	spriteComponentLegs->SetAnimationRectSize(XMUINT2(10, 1));
	spriteComponentLegs->SetAnimationSpeed(10 * walkAnimationSpeed);
	spriteComponentLegs->SetPlaying(false, false);
	spriteComponentBody->SetUseTranslucency(true);
	originalLegTint = spriteComponentLegs->GetTint();

	spriteComponentShadow = AddComponent<CSpriteComponent>(NAME_OF(spriteComponentShadow));
	spriteComponentShadow->LoadTextureWIC("Resources/Game/Characters/JonathanWicke-shadow.png");
	spriteComponentShadow->SetPosition(XMFLOAT3(0, 0, 2));
	spriteComponentShadow->SetScale(XMFLOAT3(1.45, 1.45, 1.45));
	spriteComponentShadow->SetUseTranslucency(true);

	spriteComponentShield = AddComponent<CSpriteComponent>(NAME_OF(spriteComponentShield));
	spriteComponentShield->LoadTextureWIC("Resources/Game/weapons/Shield.png");
	spriteComponentShield->SetPosition(XMFLOAT3(0, 0, -1));
	spriteComponentShield->SetScale(XMFLOAT3(1.45, 1.45, 1.45));
	spriteComponentShield->SetUseTranslucency(true);
	spriteComponentShield->SetShouldDraw(false);

	colComponent = new CollisionComponent("Character 1", this);
	colComponent->SetCollider(64.0f, 64.0f);

	weaponComponent = AddComponent<WeaponInterface>(NAME_OF(weaponComponent));
	weaponComponent->SetUserType(USERTYPE::PLAYER);
	weaponComponent->SetWeapon(new Dagger());

	weaponSprite = AddComponent<CSpriteComponent>(NAME_OF(weaponSprite));
	UpdateWeaponSprite();
	weaponSprite->SetPosition(Vector3(spriteComponentBody->GetSpriteSize().y / 2, -int(spriteComponentBody->GetSpriteSize().x - 40), 0));
	weaponSprite->SetRotation(-1.5708); // 90 Degrees in radians.
	weaponSprite->SetTextureOffset(weaponComponent->GetCurrentWeapon()->GetTextureOffset());
	weaponSprite->SetRenderRect(weaponComponent->GetCurrentWeapon()->GetRenderRect());
	weaponSprite->SetScale(weaponComponent->GetCurrentWeapon()->GetScale());

	CEntity* t = Engine::CreateEntity<weaponUI>();
	t->SetPosition(XMFLOAT3(0, 0, -90));
	t = Engine::CreateEntity<CursorEntity>();
	t->SetPosition(XMFLOAT3(0, 0, -110));

	camera = AddComponent<CCameraComponent>(NAME_OF(camera));
	camera->SetAttachedToParent(false);
	CameraManager::SetRenderingCamera(camera);

	SetVisible(true);
}

/**
 * Function inherited from interface
 * Will use horizontal key inputs to add horizontal movement
 * 
 * \param dir - The direction of movement, negative for left, positive for right
 * \param deltaTime - Time since the last frame
 */
void PlayerCharacter::PressedHorizontal(int dir, float deltaTime)
{
	movementVec.x += dir;
}

/**
 * Function inherited from interface
 * Will use vertical key inputs to add vertical movement
 * 
 * \param dir  - The direction of movement, negative for down, positive for up
 * \param deltaTime - Time since the last frame
 */
void PlayerCharacter::PressedVertical(int dir, float deltaTime)
{
	movementVec.y += dir;
}
/**
 * Function inherited from interface
 * Will interact with objects in the world if one is available
 * 
 */
void PlayerCharacter::PressedInteract()
{
	
}
/**
* Function inherited from interface
* Will drop the characters currently equipped item
* Will return early if the EquippedItem is null
*/
void PlayerCharacter::PressedDrop()
{

}

PlayerCharacter::~PlayerCharacter()
{
	AudioController::RemoveListener();
}

static bool animating = false;
void PlayerCharacter::Attack()
{
	XMFLOAT3 screenVec = XMFLOAT3(InputManager::mousePos.x - Engine::windowWidth * 0.5f, -InputManager::mousePos.y + Engine::windowHeight * 0.5f, InputManager::mousePos.z);
	screenVec = Math::FromScreenToWorld(screenVec);

	Vector3 attackDir = (Vector3(screenVec.x, screenVec.y, screenVec.z)) - GetPosition();

	
	// Impomptu Animation Code for weapons.
	Weapon* weapon = weaponComponent->GetCurrentWeapon();
	if(weapon->GetName() == "Crossbow")	// Crossbow exclusive animations, can be extended to include any animations that are 2 cycle.
	{
		if(weapon->GetCanFire())
		{
			weaponSprite->SetTextureOffset(DirectX::XMFLOAT2(0, 0));
		}

	}
	else if(weapon->GetName() == "Dagger" || weapon->GetName() == "Rapier" || weapon->GetName() == "Longsword" && !animating)	// Positional based animations for melee.
	{
		if (weapon->GetCanFire())
		{
			weaponSprite->SetPosition(weaponSprite->GetPosition().x + 10, weaponSprite->GetPosition().y, weaponSprite->GetPosition().z);
			animating = true;
		}
	}

	if (weaponComponent->OnFire(GetPosition(), attackDir))
		SoundManager::PlaySound(weaponComponent->GetCurrentWeapon()->GetAttackSound(), GetPosition());

	if (!GetVisible() || !pickupTimerCallback) return;

	pickupTimerCallback();
}

void PlayerCharacter::Update(float deltaTime)
{
	timeElapsed += deltaTime;

	Weapon* weapon = weaponComponent->GetCurrentWeapon();
	
	// Set crossbow animation to empty bow when we cant fire or out of ammo.
	if(weapon->GetName() == "Crossbow")
	{
		if(!weapon->GetCanFire() || weapon->GetAmmo() <= 0)
		{
			weaponSprite->SetTextureOffset(DirectX::XMFLOAT2(64, 0));
		}
	}

	// Reset melee animation if it has been triggered and we can fire again.
	if(weapon->GetCanFire() && animating)
	{
		weaponSprite->SetPosition(weaponSprite->GetPosition().x - 10, weaponSprite->GetPosition().y, weaponSprite->GetPosition().z);
		animating = false;
	}

	ResolveMovement(deltaTime);

	Vector3 mousePos = Vector3(InputManager::mousePos.x - Engine::windowWidth * 0.5f, -InputManager::mousePos.y + Engine::windowHeight * 0.5f, 1);
	
	AimAtMouse(mousePos);

	colComponent->SetPosition(GetPosition());
	weaponComponent->Update(deltaTime);
	weaponSprite->SetTextureOffset(weaponComponent->GetCurrentWeapon()->GetTextureOffset());

	FootstepTimer(deltaTime);

	movementVec = { 0,0 };
	movementVel = XMFLOAT2(movementVel.x * (1 - deltaTime * walkDrag), movementVel.y * (1 - deltaTime * walkDrag));

	PickupTimer(deltaTime);

	

}

void PlayerCharacter::ResolveMovement(const float& deltaTime)
{
	if (movementVec.Magnitude() > 0.01f)
	{
		movementVec = movementVec.Normalize();
		movementVel = XMFLOAT2(movementVec.x * walkSpeed * deltaTime * 10 + movementVel.x, movementVec.y * walkSpeed * deltaTime * 10 + movementVel.y);
	}

	AddMovement(movementVel, deltaTime);

	if (movementVec.x == 0 && movementVec.y == 0 && spriteComponentBody->GetPlaying())
	{
		spriteComponentBody->SetPlaying(false, true);
		spriteComponentLegs->SetPlaying(false, true);
	}
	else if (!spriteComponentBody->GetPlaying())
	{
		spriteComponentBody->SetPlaying(true, false);
		spriteComponentLegs->SetPlaying(true, false);
	}
}

void PlayerCharacter::AimAtMouse(const Vector3& mousePos)
{
	Vector3 mousePercent = mousePos / Vector3(Engine::windowWidth, Engine::windowHeight, 1);
	mousePercent.z = 0;

	camera->SetPosition(mousePercent * cameraMovementScalar + GetPosition());
	
	XMFLOAT3 mousePosFloat3 = XMFLOAT3(mousePos.x, mousePos.y, mousePos.z);
	XMFLOAT3 screenVec = Math::FromScreenToWorld(mousePosFloat3);

	LookAt(Vector3(screenVec.x, screenVec.y, screenVec.z));

	
}

void PlayerCharacter::FootstepTimer(float deltaTime)
{
	if (movementVec.Magnitude() < 0.01f) return;
	
	stepTimer += deltaTime;
	if (stepTimer >= timeBetweenSteps)
	{
		//footstepAudioEmitter->Play();
		SoundManager::PlaySound("StepSound", GetPosition());
		stepTimer = 0;
	}
}

void PlayerCharacter::EquipWeapon(Weapon* weapon)
{
	weaponComponent->SetWeapon(weapon);
	UpdateWeaponSprite();
	weaponSprite->SetTextureOffset(weaponComponent->GetCurrentWeapon()->GetTextureOffset());
	weaponSprite->SetRenderRect(weaponComponent->GetCurrentWeapon()->GetRenderRect());
	weaponSprite->SetScale(weaponComponent->GetCurrentWeapon()->GetScale());
	movementVec = {0,0};
}

void PlayerCharacter::UpdateWeaponSprite()
{
	HRESULT hr;
	if (IO::FindExtension(weaponComponent->GetCurrentWeapon()->GetIconPath()) == "dds")
	{
		hr = weaponSprite->LoadTexture(weaponComponent->GetCurrentWeapon()->GetIconPath());
		if (FAILED(hr))
		{
			Debug::LogHResult(hr, "Weapon Tried to load texture using path: %s but the loader returned failure.", weaponComponent->GetCurrentWeapon()->GetIconPath().c_str());
			return;
		}
	}
	else
	{
		hr = weaponSprite->LoadTextureWIC(weaponComponent->GetCurrentWeapon()->GetIconPath());
		if (FAILED(hr))
		{
			Debug::LogHResult(hr, "Weapon Tried to load texture using path: %s but the loader returned failure.", weaponComponent->GetCurrentWeapon()->GetIconPath().c_str());
			return;
		}
	}
}

void PlayerCharacter::ApplyDamage(float damage)
{
	Debug::Log("Hit");
	if (hasShield)
	{
		ToggleShield(false);
		SoundManager::PlaySound("ShieldHit", GetPosition());
		return;
	}

	SetHealth(GetHealth() - damage);
	if (GetHealth() <= 0.0f)
	{
		//playersController[0]->Unpossess();
		SoundManager::PlaySound("DeathSound", GetPosition());
		CUIManager::GetCanvas("DeathMenu")->SetVisibility(true);
		Engine::paused = true;
		//Engine::DestroyEntity(this);
	}
		
}

void PlayerCharacter::ApplyDamage(float damage, const std::string& onHitSound)
{
	SoundManager::PlaySound(onHitSound, GetPosition());
	ApplyDamage(damage);
}

void PlayerCharacter::LookAt(Vector3 pos)
{
	Vector3 up = { 0.0f, 1.0f, 0.0f };

	Vector3 dir = pos - GetPosition();

	if (dir == Vector3(0, 0, 0))
		return;

	auto normDir = dir.Normalize();

	float dot = up.Dot(dir);
	float det = up.x * dir.y - up.y * dir.x;

	const float degToRad = 0.0174533f;

	SetRotation(atan2f(det, dot) + 90 * degToRad);
}

/**
* Checks the pickup item type and activates the functionality for that pickup.
* E.g, Invisibility scroll will make the player invisible and bind a callback to the timer to make the player visible after a certain amount of time.
*/
void PlayerCharacter::UsePickup(const std::string& pickupToUse, float activeTime)
{
	if (pickupToUse == "InvisibilityScroll")
	{
		pickupActive = true;
		pickupTimer = 0;
		pickupActiveTime = activeTime;

		visible = false;
		pickupTimerCallback = std::bind(&PlayerCharacter::InvisibilityCallback, this);

		spriteComponentBody->SetTint(XMFLOAT4(originalSpriteTint.x, originalSpriteTint.y, originalSpriteTint.z, -0.75f));
		spriteComponentLegs->SetTint(XMFLOAT4(originalLegTint.x, originalLegTint.y, originalLegTint.z, -0.75f));
	} 
	else if (pickupToUse == "ShieldScroll")
	{
		ToggleShield(true);
	}
}

void PlayerCharacter::PressedUse()
{
}

/**
* Function used as a callback for when the invisibility pickup runs out
*/
void PlayerCharacter::InvisibilityCallback()
{
	pickupActive = false;
	SoundManager::PlaySound("DeactivateInvis", GetPosition());
	pickupTimerCallback = nullptr;
	spriteComponentBody->SetTint(originalSpriteTint);
	spriteComponentLegs->SetTint(originalLegTint);
	visible = true;
	
}

/**
* Function used to time how long a pickup has been active and call the appropriate callback when it runs out
*/
void PlayerCharacter::PickupTimer(float deltaTime)
{
	if (!pickupActive) return;

	pickupTimer += deltaTime;

	if (pickupTimer >= pickupActiveTime)
	{
		pickupActive = false;
		pickupTimerCallback();
	}
}
/**
 * Function used to toggle the visibility of the characters sprites.
 * 
 * \param isVisible - Whether or not the character should be visible
 */
void PlayerCharacter::ToggleVisibility(bool isVisible)
{
	visible = isVisible;
	spriteComponentBody->SetShouldDraw(visible);
	spriteComponentLegs->SetShouldDraw(visible);
	spriteComponentShadow->SetShouldDraw(visible);
	weaponSprite->SetShouldDraw(visible);
}

void PlayerCharacter::ToggleShield(bool shield)
{
	hasShield = shield;
	spriteComponentShield->SetShouldDraw(shield);
}

