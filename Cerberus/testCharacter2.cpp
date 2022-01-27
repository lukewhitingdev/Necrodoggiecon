#include "testCharacter2.h"

testCharacter2::testCharacter2()
{
	spriteComponent = AddComponent<CSpriteComponent>();
	spriteComponent->LoadTexture("Resources\\birb.dds");
	spriteComponent->SetRenderRect(XMUINT2(128, 128));
	spriteComponent->SetSpriteSize(XMUINT2(128, 128));

	spriteComponent->SetTint(XMFLOAT4(float(rand() % 2 * .5), float(rand() % 2 * .5), float(rand() % 2 * .5), 0));

	if (float(rand() % 2))
		spriteComponent->SetScale(-1, 1, 1);
}

void testCharacter2::PressedHorizontal(int dir, float deltaTime)
{
	AddHorizontalMovement(dir, speed, deltaTime);
}

void testCharacter2::PressedVertical(int dir, float deltaTime)
{
	AddVerticalMovement(dir, speed, deltaTime);
}

void testCharacter2::Update(float deltaTime)
{
}

void testCharacter2::PressedInteract()
{
}

void testCharacter2::PressedDrop()
{
}
