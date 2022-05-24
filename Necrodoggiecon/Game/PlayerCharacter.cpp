#include "PlayerCharacter.h"
#include "CDroppedItem.h"
#include "CEquippedItem.h"
#include "Cerberus/Core/Utility/Math/Math.h"
#include "Cerberus\Core\Components\CCameraComponent.h"
#include "Cerberus/Core/Utility/IO.h"
#include "Necrodoggiecon/Game/PlayerController.h"
#include "Cerberus/Core/Utility/CameraManager/CameraManager.h"
#include <Necrodoggiecon/Weapons/Ranged/MagicMissile.h>

PlayerCharacter::PlayerCharacter()
{
	SetShouldMove(true);

	spriteComponentBody = AddComponent<CAnimationSpriteComponent>();
	spriteComponentBody->SetName(NAME_OF(spriteComponentBody));

	spriteComponentBody->LoadTextureWIC("Resources/Game/Characters/JonathanWicke-sheet.png");
	spriteComponentBody->SetSpriteSize(XMUINT2(64, 64));
	spriteComponentBody->SetRenderRect(XMUINT2(44, 44));
	spriteComponentBody->SetAnimationRectSize(XMUINT2(2, 1));
	spriteComponentBody->SetAnimationSpeed(2 * walkAnimationSpeed);
	spriteComponentBody->SetPlaying(false, false);

	spriteComponentLegs = AddComponent<CAnimationSpriteComponent>();
	spriteComponentLegs->LoadTextureWIC("Resources/Game/Characters/legsSpriteSheet.png");
	spriteComponentLegs->SetPosition(XMFLOAT3(0, 0, 1));
	spriteComponentLegs->SetScale(XMFLOAT3(2, 1.5, 1.5));
	spriteComponentLegs->SetRenderRect(XMUINT2(29, 22));
	spriteComponentLegs->SetSpriteSize(XMUINT2(29, 22));
	spriteComponentLegs->SetAnimationRectSize(XMUINT2(10, 1));
	spriteComponentLegs->SetAnimationSpeed(10 * walkAnimationSpeed);
	spriteComponentLegs->SetPlaying(false, false);

	spriteComponentShadow = AddComponent<CSpriteComponent>();
	spriteComponentShadow->LoadTextureWIC("Resources/Game/Characters/JonathanWicke-shadow.png");
	spriteComponentShadow->SetPosition(XMFLOAT3(0, 0, 2));
	spriteComponentShadow->SetScale(XMFLOAT3(1.45, 1.45, 1.45));
	spriteComponentShadow->SetUseTranslucency(true);

	colComponent = new CollisionComponent("Character 1", this);
	colComponent->SetCollider(64.0f, 64.0f);

	loadNoise = AddComponent<CAudioEmitterComponent>();
	loadNoise->Load("Resources/Game/TestShortAudio.wav");

	loadNoise->SetRange(10000.0f);

	weaponComponent = AddComponent<WeaponInterface>();
	weaponComponent->SetUserType(USERTYPE::PLAYER);
	weaponComponent->SetWeapon(new Crossbow());

	weaponSprite = AddComponent<CSpriteComponent>();
	UpdateWeaponSprite();
	weaponSprite->SetPosition(Vector3(spriteComponentBody->GetSpriteSize().y / 2, -int(spriteComponentBody->GetSpriteSize().x - 40), 0));
	weaponSprite->SetRotation(-1.5708); // 90 Degrees in radians.

	camera = AddComponent<CCameraComponent>();
	camera->SetAttachedToParent(false);
	CameraManager::SetRenderingCamera(camera);
}

void PlayerCharacter::PressedHorizontal(int dir, float deltaTime)
{
	movementVec.x += dir;
}

void PlayerCharacter::PressedVertical(int dir, float deltaTime)
{
	movementVec.y += dir;
}

void PlayerCharacter::PressedInteract()
{
	weaponComponent->SetWeapon(new Longsword());

	if (droppedItem == nullptr) return;

	equippedItem = droppedItem->OnEquip(this);
	Engine::DestroyEntity(droppedItem);
	droppedItem = nullptr;
}

void PlayerCharacter::PressedDrop()
{
	weaponComponent->SetWeapon(new Rapier());

	if (equippedItem == nullptr) return;

	droppedItem = equippedItem->Drop();
	Engine::DestroyEntity(equippedItem);
	equippedItem = nullptr;
}

void PlayerCharacter::Attack()
{
	
	XMFLOAT3 screenVec = XMFLOAT3(Inputs::InputManager::mousePos.x - Engine::windowWidth * 0.5f, -Inputs::InputManager::mousePos.y + Engine::windowHeight * 0.5f, Inputs::InputManager::mousePos.z);
	screenVec = Math::FromScreenToWorld(screenVec);

	Vector3 attackDir = (Vector3(screenVec.x, screenVec.y, screenVec.z)) - GetPosition();

	weaponComponent->OnFire(GetPosition(), attackDir);
}

void PlayerCharacter::Update(float deltaTime)
{
	timeElapsed += deltaTime;

	ResolveMovement(deltaTime);

	Vector3 mousePos = Vector3(Inputs::InputManager::mousePos.x - Engine::windowWidth * 0.5f, -Inputs::InputManager::mousePos.y + Engine::windowHeight * 0.5f, 1);
	
	AimAtMouse(mousePos);

	colComponent->SetPosition(GetPosition());
	weaponComponent->Update(deltaTime);

	movementVec = { 0,0 };
	movementVel = XMFLOAT2(movementVel.x * (1 - deltaTime * walkDrag), movementVel.y * (1 - deltaTime * walkDrag));
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

void PlayerCharacter::EquipWeapon(Weapon* weapon)
{
	weaponComponent->SetWeapon(weapon);
	UpdateWeaponSprite();
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
	SetHealth(GetHealth() - damage);
	if (GetHealth() <= 0.0f)
	{
		playersController[0]->Unpossess();
		Engine::DestroyEntity(this);
	}
		
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