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

	SetPosition(Vector3(Inputs::InputManager::mousePos.x - Engine::windowWidth * 0.5f, -Inputs::InputManager::mousePos.y + Engine::windowHeight * 0.5f, -100));
	
	/*if (Input::GetKeyState(Keys::LMB))
		sprite->SetRotation(3.14159 / 4);
	else
		sprite->SetRotation(0);*/

	std::stringstream ss;
	ss << "X:" << round(GetPosition().x) << " Y:" << round(GetPosition().y);
	text->SetText(ss.str());

	if (Inputs::InputManager::IsMouseButtonPressed(Inputs::InputManager::RButton))
	{
		if (!mouseRHeld)
		{
			mouseRHeld = true;
			mouseOffset = Inputs::InputManager::mousePos;
		}

		Vector3 mousePos = (Inputs::InputManager::mousePos - mouseOffset) / Engine::camera.GetZoom();
		mouseOffset = Inputs::InputManager::mousePos;

		Engine::camera.SetCameraPosition(XMFLOAT4(-mousePos.x + Engine::camera.GetCameraPosition().x, mousePos.y + Engine::camera.GetCameraPosition().y, -3, 1));
	}
	else
	{
		if (mouseRHeld)
			mouseRHeld = false;
	}
}

CursorEntity::~CursorEntity()
{

}