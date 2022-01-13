#include "testClass.h"
#include "Utility/DebugOutput/Debug.h"
#include "../CSpriteComponent.h"

TestClass::TestClass()
{
	Debug::Log("init test class!\n");

	sprite = AddComponent<CSpriteComponent>();
	if (rand() % 2)
	{
		sprite->LoadTexture(L"Resources\\Man.dds");
		position.z = -10;
	}
	else
	{
		sprite->LoadTexture(L"Resources\\landscape.dds");
	}

	sprite->SetRenderRect(XMUINT2(sprite->GetRenderRect().x * 2, sprite->GetRenderRect().y * 2));
	sprite->spriteSize = XMUINT2(sprite->spriteSize.x * 2, sprite->spriteSize.y * 2);

	rotDir = rand() % 2;
}

void TestClass::Update(float deltaTime)
{
	//CEntity::Update(deltaTime);

	//position.x += deltaTime * 10;

	rotation += ((2 * rotDir) - 1) * deltaTime;

	//scale.y += deltaTime * .3;

}

TestClass::~TestClass()
{
	Debug::Log("destroy test class!\n");
}
