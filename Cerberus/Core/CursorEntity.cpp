#include "CursorEntity.h"
#include "Utility/DebugOutput/Debug.h"
#include "../CTextRenderComponent.h"
#include <sstream>
#include "CCamera.h"

CursorEntity::CursorEntity()
{
	SetPosition(0, 0, -100);

	sprite = AddComponent<CSpriteComponent>();
	sprite->LoadTexture("Resources\\cursorSS.dds");
	sprite->SetRenderRect(XMUINT2(16, 16));
	sprite->SetSpriteSize(XMUINT2(64, 64));
	sprite->ui = true;

	text = AddComponent<CTextRenderComponent>();
	text->SetJustification(TextJustification::Center);
	text->SetPosition(0, -48, 0);
	text->ui = true;
}

void CursorEntity::Update(float deltaTime)
{
	timeElapsed += deltaTime;

	unsigned char row = 0;
	if (Inputs::InputManager::IsMouseButtonPressed(Inputs::InputManager::RButton))
		row = 2;
	else if (Inputs::InputManager::IsMouseButtonPressed(Inputs::InputManager::LButton))
		row = 1;

	const float speed = 2;
	sprite->SetTextureOffset(XMFLOAT2(round(timeElapsed * speed) * sprite->GetRenderRect().x, row * sprite->GetRenderRect().y));

	SetPosition(Vector3(Inputs::InputManager::mousePos.x - Engine::windowWidth * 0.5f, -Inputs::InputManager::mousePos.y + Engine::windowHeight * 0.5f, GetPosition().z));

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

		Engine::camera.SetCameraPosition(XMFLOAT4(-mousePos.x + Engine::camera.GetCameraPosition().x, mousePos.y + Engine::camera.GetCameraPosition().y, Engine::camera.GetCameraPosition().z, Engine::camera.GetCameraPosition().w));
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
