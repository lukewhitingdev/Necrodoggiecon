#include "testClass.h"
#include "Utility/DebugOutput/Debug.h"
#include "../CSpriteComponent.h"

TestClass::TestClass()
{
	Debug::Log("init test class!\n");

	sprite = new CSpriteComponent();
	sprite->LoadTexture(L"Resources\\stone.dds");
	components.push_back(sprite);
}

void TestClass::Update(float deltaTime)
{
	//CEntity::Update(deltaTime);

	position.x += deltaTime;

	rotation += sin(deltaTime);

	scale.y += deltaTime * .3;

}

TestClass::~TestClass()
{
	Debug::Log("destroy test class!\n");
}
