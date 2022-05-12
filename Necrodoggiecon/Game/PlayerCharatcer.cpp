#include "PlayerCharacter.h"
#include "CDroppedItem.h"
#include "CEquippedItem.h"
#include "Cerberus/Core/Utility/Math/Math.h"

PlayerCharacter::PlayerCharacter()
{
	spriteComponent = AddComponent<CAnimationSpriteComponent>();
	spriteComponent->LoadTextureWIC("Resources\\manSS.png");
	spriteComponent->SetRenderRect(XMUINT2(16, 16));
	spriteComponent->SetSpriteSize(XMUINT2(64, 64));
	spriteComponent->SetAnimationSpeed(15);
	spriteComponent->SetAnimationRectSize(XMUINT2(8, 1));

	colComponent = new CollisionComponent("Character 1");
}

void PlayerCharacter::PressedHorizontal(int dir, float deltaTime)
{
	AddHorizontalMovement(dir, speed, deltaTime);

	if (dir > 0)
		spriteComponent->SetAnimationRectPosition(XMUINT2(0, 1));
	else
		spriteComponent->SetAnimationRectPosition(XMUINT2(0, 2));
}

void PlayerCharacter::PressedVertical(int dir, float deltaTime)
{
	AddVerticalMovement(dir, speed, deltaTime);

	if (dir > 0)
		spriteComponent->SetAnimationRectPosition(XMUINT2(0, 0));
	else
		spriteComponent->SetAnimationRectPosition(XMUINT2(0, 3));
}

void PlayerCharacter::PressedInteract()
{
	if (droppedItem == nullptr) return;

	equippedItem = droppedItem->OnEquip(this);
	Engine::DestroyEntity(droppedItem);
	droppedItem = nullptr;
}

void PlayerCharacter::PressedDrop()
{
	if (equippedItem == nullptr) return;

	droppedItem = equippedItem->Drop();
	Engine::DestroyEntity(equippedItem);
	equippedItem = nullptr;
}

void PlayerCharacter::Update(float deltaTime)
{
	timeElapsed += deltaTime;

	XMFLOAT3 screenVec = XMFLOAT3(Inputs::InputManager::mousePos.x - Engine::windowWidth * 0.5f, -Inputs::InputManager::mousePos.y + Engine::windowHeight * 0.5f, Inputs::InputManager::mousePos.z);
	screenVec = Math::FromScreenToWorld(screenVec);

	//LookAt(Vector3(screenVec.x, screenVec.y, screenVec.z));

	colComponent->SetPosition(GetPosition());
}

void PlayerCharacter::HasCollided(CollisionComponent* collidedObject)
{
	if (collidedObject->GetName() == "Wall")
		Debug::Log("Player has collided with a wall");
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

	SetRotation(atan2f(det, dot));
}