#include "PlayerCharacter.h"
#include "CDroppedItem.h"
#include "CEquippedItem.h"
#include "Cerberus/Core/Utility/Math/Math.h"
#include "Cerberus\Core\Components\CCameraComponent.h"
#include "Game/PickupItemData.h"

PlayerCharacter::PlayerCharacter()
{
	spriteComponentBody = AddComponent<CAnimationSpriteComponent>();
	spriteComponentBody->LoadTextureWIC("Resources/Characters/JonathanWicke-sheet.png");
	spriteComponentBody->SetSpriteSize(XMUINT2(64, 64));
	spriteComponentBody->SetRenderRect(XMUINT2(44, 44));
	spriteComponentBody->SetAnimationRectSize(XMUINT2(2, 1));
	spriteComponentBody->SetAnimationSpeed(2 * walkAnimationSpeed);
	spriteComponentBody->SetPlaying(false, false);

	spriteComponentLegs = AddComponent<CAnimationSpriteComponent>();
	spriteComponentLegs->LoadTextureWIC("Resources/Characters/legsSpriteSheet.png");
	spriteComponentLegs->SetPosition(XMFLOAT3(0, 0, 1));
	spriteComponentLegs->SetScale(XMFLOAT3(2, 1.5, 1.5));
	spriteComponentLegs->SetRenderRect(XMUINT2(29, 22));
	spriteComponentLegs->SetSpriteSize(XMUINT2(29, 22));
	spriteComponentLegs->SetAnimationRectSize(XMUINT2(10, 1));
	spriteComponentLegs->SetAnimationSpeed(10 * walkAnimationSpeed);
	spriteComponentLegs->SetPlaying(false, false);

	spriteComponentShadow = AddComponent<CSpriteComponent>();
	spriteComponentShadow->LoadTextureWIC("Resources/Characters/JonathanWicke-shadow.png");
	spriteComponentShadow->SetPosition(XMFLOAT3(0, 0, 2));
	spriteComponentShadow->SetScale(XMFLOAT3(1.45, 1.45, 1.45));
	spriteComponentShadow->SetUseTranslucency(true);

	colComponent = new CollisionComponent("Character 1", this);

	loadNoise = AddComponent<CAudioEmitterComponent>();
	loadNoise->Load("Resources/TestShortAudio.wav");

	loadNoise->SetRange(10000.0f);

	weaponComponent = AddComponent<Weapon>();
	weaponComponent->SetWeapon("Crossbow");
	weaponComponent->SetUserType(USERTYPE::PLAYER);
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
	AddHorizontalMovement(dir, speed, deltaTime);
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
	AddVerticalMovement(dir, speed, deltaTime);
}
/**
 * Function inherited from interface
 * Will interact with objects in the world if one is available
 * 
 */
void PlayerCharacter::PressedInteract()
{
	if (droppedItem == nullptr) return;

	equippedItem = droppedItem->OnEquip(this);
	Engine::DestroyEntity(droppedItem);
	droppedItem = nullptr;
}
/**
* Function inherited from interface
* Will drop the characters currently equipped item
* Will return early if the EquippedItem is null
*/
void PlayerCharacter::PressedDrop()
{
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

	if (GetVisible()) return;

	pickupTimerCallback();
}

void PlayerCharacter::Update(float deltaTime)
{
	timeElapsed += deltaTime;

	if (movementVec.x == 0 && movementVec.y == 0 && spriteComponentBody->GetPlaying())
	{
		spriteComponentBody->SetPlaying(false, true);
		spriteComponentLegs->SetPlaying(false, true);
	}
	else if(!spriteComponentBody->GetPlaying())
	{
		spriteComponentBody->SetPlaying(true, false);
		spriteComponentLegs->SetPlaying(true, false);
	}

	XMFLOAT3 screenVec = XMFLOAT3(Inputs::InputManager::mousePos.x - Engine::windowWidth * 0.5f, -Inputs::InputManager::mousePos.y + Engine::windowHeight * 0.5f, Inputs::InputManager::mousePos.z);
	screenVec = Math::FromScreenToWorld(screenVec);

	LookAt(Vector3(screenVec.x, screenVec.y, screenVec.z));

	colComponent->SetPosition(GetPosition());

	movementVec = {0,0};

	PickupTimer(deltaTime);
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

	SetRotation(atan2f(det, dot) + 90 * 0.0174533);
}

/**
* Checks the pickup item type and activates the functionality for that pickup.
* E.g, Invisibility scroll will make the player invisible and bind a callback to the timer to make the player visible after a certain amount of time.
*/
void PlayerCharacter::UsePickup(PickupItemData* itemToPickup)
{
	if (itemToPickup == nullptr)return;

	pickupActive = true;
	pickupTimer = 0;
	pickupActiveTime = itemToPickup->GetPickupTime();

	switch (itemToPickup->GetPickupType())
	{
	case PickupType::NECRODOGGICON_PAGE:
		Debug::Log("Pickup Necrodoggiecon Page \n");
		break;
	case PickupType::CHARM_SCROLL:
		Debug::Log("Use Charm Scroll \n");
		break;
	case PickupType::INVISIBILITY_SCROLL:
		pickupTimerCallback = std::bind(&PlayerCharacter::InvisibilityCallback, this);
		ToggleVisibility(false);
		Debug::Log("Use Invisibility Scroll \n");
		break;
	case PickupType::SEEING_SCROLL:
		Debug::Log("Use Seeing Scroll \n");
		break;
	case PickupType::SHIELD_SCROLL:
		Debug::Log("Use Shield Scroll \n");
		break;
	default:
		break;
	}

	Engine::DestroyEntity(equippedItem);
	equippedItem = nullptr;
}
/**
* Function inherited from interface
* Will use the currently equipped item
* First checks the item type and then uses the item appropriately
*/
void PlayerCharacter::PressedUse()
{
	if (equippedItem == nullptr) return;

	ItemType itemType = equippedItem->GetItemData()->GetItemType();

	if (itemType == ItemType::EQUIPPABLE)
	{

	}
	else if (itemType == ItemType::PICKUP)
	{
		UsePickup(static_cast<PickupItemData*>(equippedItem->GetItemData()));
	}
}

/**
* Function used as a callback for when the invisibility pickup runs out
*/
void PlayerCharacter::InvisibilityCallback()
{
	Debug::Log("invisCB");
	ToggleVisibility(true);
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
}
