#include "testCharacter.h"
#include "CDroppedItem.h"
#include "CEquippedItem.h"

testCharacter::testCharacter()
{
	spriteComponent = AddComponent<CSpriteComponent>();
	spriteComponent->LoadTexture("Resources\\birb.dds");
	spriteComponent->SetRenderRect(XMUINT2(128, 128));
	spriteComponent->SetSpriteSize(XMUINT2(128, 128));

	spriteComponent->SetTint(XMFLOAT4(float(rand() % 2 * .5), float(rand() % 2 * .5), float(rand() % 2 * .5), 0));

	colComponent = new CollisionComponent("Character 1");

	if (float(rand() % 2))
		spriteComponent->SetScale(-1, 1, 1);

	timeElapsed = float(rand() / 100);

	weapon = new weapons("Dagger", USERTYPE::PLAYER);
}

void testCharacter::PressedHorizontal(int dir, float deltaTime)
{
	AddHorizontalMovement(dir, speed, deltaTime);
	
}

void testCharacter::PressedVertical(int dir, float deltaTime)
{
	AddVerticalMovement(dir, speed, deltaTime);
}

void testCharacter::PressedInteract()
{
	Vector3 attackDir = (Vector3(Inputs::InputManager::mousePos.x - Engine::windowWidth * 0.5f, -Inputs::InputManager::mousePos.y + Engine::windowHeight * 0.5f, GetPosition().z)) - GetPosition();

	weapon->OnFire(GetPosition(), attackDir);
	/*if (droppedItem == nullptr) return;

	equippedItem = droppedItem->OnEquip(this);
	Engine::DestroyEntity(droppedItem);
	droppedItem = nullptr;*/

}

void testCharacter::PressedDrop()
{
	if (equippedItem == nullptr) return;

	droppedItem = equippedItem->Drop();
	Engine::DestroyEntity(equippedItem);
	equippedItem = nullptr;
}

void testCharacter::Update(float deltaTime)
{
	timeElapsed += deltaTime;

	const uint32_t animSpeed = 24;
	spriteComponent->SetTextureOffset(XMFLOAT2(round(timeElapsed * animSpeed) * 128, float((int(round(timeElapsed * animSpeed) / 5) % 2)) * 128));

	LookAt(Vector3(Inputs::InputManager::mousePos.x - Engine::windowWidth * 0.5f, -Inputs::InputManager::mousePos.y + Engine::windowHeight * 0.5f, GetPosition().z));

	colComponent->SetPosition(GetPosition());

	weapon->Update(deltaTime);

}

void testCharacter::HasCollided(CollisionComponent* collidedObject)
{
	/*if (collidedObject->GetName() == "Wall")
		Debug::Log("Player has collided with a wall");*/
}

void testCharacter::LookAt(Vector3 pos)
{
	Vector3 up = { 0.0f, 1.0f, 0.0f };

	Vector3 dir = pos - GetPosition();
	auto normDir = dir.Normalize();

	float dot = up.Dot(dir);
	float det = up.x * dir.y - up.y * dir.x;

	SetRotation(atan2f(det, dot));
}