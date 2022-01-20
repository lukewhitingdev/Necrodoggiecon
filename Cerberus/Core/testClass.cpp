#include "testClass.h"
#include "Utility/DebugOutput/Debug.h"
#include "../CTextRenderComponent.h"
#include <sstream>
#include "CCamera.h"

TestClass::TestClass()
{
	Debug::Log("init test class!\n");

	sprite = AddComponent<CSpriteComponent>();
	sprite->LoadTexture("Resources\\cursorSS.dds");
	sprite->SetRenderRect(XMUINT2(16, 16));
	sprite->SetSpriteSize(XMUINT2(64, 64));
	sprite->SetPosition(0, 0, -100);

	text = AddComponent<CTextRenderComponent>();
	text->justification = TextJustification::Center;
}

void TestClass::Update(float deltaTime)
{
	//CEntity::Update(deltaTime);

	timeElapsed += deltaTime;

	const float speed = 2;
	sprite->SetTextureOffset(XMFLOAT2(round(timeElapsed * speed) * 16, 0));

	float invZoom = 1 / Engine::camera.GetZoom();
	SetPosition(Vector3(((Input::mousePos.x - Engine::windowWidth * 0.5f ) * invZoom) + Engine::camera.GetCameraPosition().x,
						((-Input::mousePos.y + Engine::windowHeight * 0.5f) * invZoom) + Engine::camera.GetCameraPosition().y,
							0));
	
	text->SetScale(invZoom);
	sprite->SetScale(invZoom);
	text->SetPosition(0, -48 * invZoom, -100);

	std::stringstream ss;
	ss << "X:" << round(GetPosition().x) << " Y:" << round(GetPosition().y);
	text->SetText(ss.str());
}

TestClass::~TestClass()
{
	Debug::Log("destroy test class!\n");
}
