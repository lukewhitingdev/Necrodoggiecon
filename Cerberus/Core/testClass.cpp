#include "testClass.h"
#include "Utility/DebugOutput/Debug.h"
#include "../CSpriteComponent.h"
#include "Utility/CollisionManager/Components/Bodies/CollisionComponent.h"

TestClass::TestClass()
{
	Debug::Log("init test class!\n");

	sprite = AddComponent<CSpriteComponent>();
	sprite->LoadTexture("Resources\\birb.dds");
	sprite->SetRenderRect(XMUINT2(128, 128));
	sprite->spriteSize = XMUINT2(128, 128);

	if (rand() % 2)
		sprite->scale.x = -1;

	timeElapsed = rand() / 100;
}

void TestClass::Update(float deltaTime)
{
	//CEntity::Update(deltaTime);

	timeElapsed += deltaTime;

	const uint32_t speed = 24;
	sprite->SetTextureOffset(XMFLOAT2(round(timeElapsed * speed) * 128, (int(round(timeElapsed * speed) / 5) % 2) * 128));
}

TestClass::~TestClass()
{
	Debug::Log("destroy test class!\n");
}
