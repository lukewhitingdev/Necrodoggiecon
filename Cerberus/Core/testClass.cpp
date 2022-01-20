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
	sprite->SetRenderRect(XMUINT2(128, 128));
	sprite->SetSpriteSize(XMUINT2(128, 128));
	sprite->SetPosition(0, 0, -1);

	text = AddComponent<CTextRenderComponent>();
	text->SetPosition(0, -84, -100);
	text->SetText("thisistext.");

	sprite->SetTint(XMFLOAT4(float(rand() % 2 * .5), float(rand() % 2 * .5), float(rand() % 2 * .5), 0));

	if (rand() % 2)
		sprite->SetScale(-1, 1, 1);

	timeElapsed = float(rand() / 100);
}

void TestClass::Update(float deltaTime)
{
	//CEntity::Update(deltaTime);

	timeElapsed += deltaTime;

	const uint32_t speed = 24;
	sprite->SetTextureOffset(XMFLOAT2(round(timeElapsed * speed) * 128, (int(round(timeElapsed * speed) / 5) % 2) * 128));

	float invZoom = 1 / Engine::camera.GetZoom();
	SetPosition(Vector3(((Input::mousePos.x - Engine::windowWidth * 0.5f ) * invZoom) + Engine::camera.GetCameraPosition().x,
						((-Input::mousePos.y + Engine::windowHeight * 0.5f) * invZoom) + Engine::camera.GetCameraPosition().y,
							0));
	
	text->SetScale(invZoom);
	text->SetPosition(0, -84 * invZoom, -100);

	std::stringstream ss;
	ss << "X:" << round(GetPosition().x) << " Y:" << round(GetPosition().y);
	text->SetText(ss.str());
}

TestClass::~TestClass()
{
	Debug::Log("destroy test class!\n");
}
