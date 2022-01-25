#include "testCharacter.h"

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
}

void testCharacter::PressedHorizontal(int dir, float deltaTime)
{
	AddHorizontalMovement(dir, speed, deltaTime);
	
}

void testCharacter::PressedVertical(int dir, float deltaTime)
{
	AddVerticalMovement(dir, speed, deltaTime);
}

void testCharacter::Update(float deltaTime)
{
	timeElapsed += deltaTime;

	const uint32_t speed = 24;
	spriteComponent->SetTextureOffset(XMFLOAT2(round(timeElapsed * speed) * 128, float((int(round(timeElapsed * speed) / 5) % 2)) * 128));

	colComponent->SetPosition(GetPosition());
}

void testCharacter::HasCollided(CollisionComponent* collided)
{
	if (collided->GetName() == "Wall")
		Debug::Log("TestCharacter Collided with Wall");
	else if (collided->GetName() == "Character 2")
		Debug::Log("TestCharacter Collided with Character 2");

}
