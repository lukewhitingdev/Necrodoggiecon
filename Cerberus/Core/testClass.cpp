#include "testClass.h"
#include "Utility/DebugOutput/Debug.h"
#include "../CSpriteComponent.h"

TestClass::TestClass()
{
	Debug::Log("init test class!\n");

	sprite = AddComponent<CSpriteComponent>();
	sprite->LoadTexture("Resources\\Tiles\\TempTileMap.dds");
	sprite->SetRenderRect(XMUINT2(tileScale, tileScale));
	sprite->SetSpriteSize(XMUINT2(tileScale, tileScale));
	sprite->SetTextureOffset(XMFLOAT2(tileScale * 2,tileScale * 2));

	//sprite->SetTint(XMFLOAT4(rand() % 2 * .5, rand() % 2 * .5, rand() % 2 * .5, 0));

	
		sprite->SetScale(15, 15, 15);

	//timeElapsed = rand() / 100;
}

void TestClass::Update(float deltaTime)
{
	//CEntity::Update(deltaTime);

	//timeElapsed += deltaTime;

	//const uint32_t speed = 24;
	//sprite->SetTextureOffset(XMFLOAT2(round(timeElapsed * speed) * 128, (int(round(timeElapsed * speed) / 5) % 2) * 128));
}

TestClass::~TestClass()
{
	Debug::Log("destroy test class!\n");
}
