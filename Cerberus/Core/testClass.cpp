#include "testClass.h"
#include "Utility/DebugOutput/Debug.h"
#include "../CSpriteComponent.h"

TestClass::TestClass()
{
	Debug::Log("init test class!\n");

	sprite = new CSpriteComponent();
	if (rand() % 2)
	{
		sprite->LoadTexture(L"Resources\\Man.dds");
		position.z = -10;
	}
	else
	{
		sprite->LoadTexture(L"Resources\\landscape.dds");
	}
	components.push_back(sprite);

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
