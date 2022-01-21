#include "testClass.h"
#include "Utility/DebugOutput/Debug.h"
#include "../CTextRenderComponent.h"
#include <sstream>
#include "CCamera.h"

TestClass::TestClass()
{
	Debug::Log("init test class!\n");


	sprite = AddComponent<CSpriteComponent>();
	sprite->LoadTexture("Resources\\birb.dds");

	//sprite->LoadTextureWIC("Resources\\dog.PNG");
	//sprite->SetTint(XMFLOAT4(float(rand() % 2 * .5), float(rand() % 2 * .5), float(rand() % 2 * .5), 0));




	timeElapsed = float(rand() / 100);
}

void TestClass::Update(float deltaTime)
{
	//CEntity::Update(deltaTime);
	const uint32_t speed = 24;
	sprite->SetTextureOffset(XMFLOAT2(round(timeElapsed * speed) * 128, float((int(round(timeElapsed * speed) / 5) % 2)) * 128));
}

TestClass::~TestClass()
{
	Debug::Log("destroy test class!\n");
}