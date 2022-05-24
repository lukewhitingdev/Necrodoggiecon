#include "testClass.h"
#include "Cerberus/Core/Utility/DebugOutput/Debug.h"
#include "Cerberus\Core\Components\CTextRenderComponent.h"
#include <sstream>
#include "Cerberus\Core\Structs\CCamera.h"

TestClass::TestClass()
{
	Debug::Log("init test class!\n");


	sprite = AddComponent<CSpriteComponent>();
	
	sprite->LoadTexture("Resources/Game/birb.dds");

	//sprite->SetTint(XMFLOAT4(float(rand() % 2 * .5), float(rand() % 2 * .5), float(rand() % 2 * .5), 0));




	timeElapsed = float(rand() / 100);
}

void TestClass::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	//CEntity::Update(deltaTime);
	const uint32_t speed = 24;
	sprite->SetTextureOffset(XMFLOAT2(round(timeElapsed * speed) * 128, float((int(round(timeElapsed * speed) / 5) % 2)) * 128));
}

TestClass::~TestClass()
{
	Debug::Log("destroy test class!\n");
}