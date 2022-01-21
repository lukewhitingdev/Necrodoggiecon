#include "CursorEntity.h"
#include "Utility/DebugOutput/Debug.h"
#include "../CTextRenderComponent.h"
#include <sstream>
#include "CCamera.h"

CursorEntity::CursorEntity()
{
	sprite = AddComponent<CSpriteComponent>();
	sprite->LoadTexture("Resources\\cursorSS.dds");
	sprite->SetRenderRect(XMUINT2(16, 16));
	sprite->SetSpriteSize(XMUINT2(64, 64));
	sprite->SetPosition(0, 0, -100);
	sprite->ui = true;

	text = AddComponent<CTextRenderComponent>();
	text->justification = TextJustification::Center;
	text->SetPosition(0, -48, -100);
	text->ui = true;
}

void CursorEntity::Update(float deltaTime)
{
	timeElapsed += deltaTime;

	const float speed = 2;
	sprite->SetTextureOffset(XMFLOAT2(round(timeElapsed * speed) * 16, 0));

	SetPosition(Vector3(Input::mousePos.x - Engine::windowWidth * 0.5f, -Input::mousePos.y + Engine::windowHeight * 0.5f, -100));
	
	/*if (Input::GetKeyState(Keys::LMB))
		sprite->SetRotation(3.14159 / 4);
	else
		sprite->SetRotation(0);*/

	std::stringstream ss;
	ss << "X:" << round(GetPosition().x) << " Y:" << round(GetPosition().y);
	text->SetText(ss.str());

	if (Input::GetKeyState(Keys::RMB))
	{
		Engine::camera.SetCameraPosition(XMFLOAT4((-Input::mousePos.x + Engine::windowWidth * .5) / Engine::camera.GetZoom(), (Input::mousePos.y - Engine::windowHeight * .5) / Engine::camera.GetZoom(), -3, 1));
	}
}

CursorEntity::~CursorEntity()
{

}
