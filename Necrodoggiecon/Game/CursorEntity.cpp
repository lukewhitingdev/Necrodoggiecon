#include "CursorEntity.h"
#include "Cerberus/Core/Utility/DebugOutput/Debug.h"
#include "Cerberus/Core/Components\CTextRenderComponent.h"
#include <sstream>
#include "Cerberus\Core\Structs\CCamera.h"
#include "Cerberus/Core/Utility/Math/Math.h"
#include "Cerberus\Core\Utility\CameraManager\CameraManager.h"

CursorEntity::CursorEntity()
{
	SetPosition(0, 0, -100);

	sprite = AddComponent<CSpriteComponent>();
	sprite->LoadTextureWIC("Resources\\cursorSS.png");
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
	CCameraComponent* camera = CameraManager::GetRenderingCamera();
	timeElapsed += deltaTime;

	unsigned char row = 0;
	if (Inputs::InputManager::IsMouseButtonPressed(Inputs::InputManager::RButton))
		row = 2;
	else if (Inputs::InputManager::IsMouseButtonPressed(Inputs::InputManager::LButton))
		row = 1;

	const float speed = 2;
	sprite->SetTextureOffset(XMFLOAT2(round(timeElapsed * speed) * float(sprite->GetRenderRect().x), row * float(sprite->GetRenderRect().y)));

	SetPosition(Vector3(Inputs::InputManager::mousePos.x - Engine::windowWidth * 0.5f, -Inputs::InputManager::mousePos.y + Engine::windowHeight * 0.5f, GetPosition().z));

	XMFLOAT3 screenVec = XMFLOAT3(GetPosition().x, GetPosition().y, GetPosition().z);
	screenVec = Math::FromScreenToWorld(screenVec);

	std::stringstream ss;
	ss << "X:" << round(screenVec.x) << " Y:" << round(screenVec.y);
	text->SetText(ss.str());

	if (Inputs::InputManager::IsMouseButtonPressed(Inputs::InputManager::RButton))
	{
		if (!mouseRHeld)
		{
			mouseRHeld = true;
			mouseOffset = Inputs::InputManager::mousePos;
		}

		Vector3 mousePos = (Inputs::InputManager::mousePos - mouseOffset) / camera->GetZoomLevel();
		mouseOffset = Inputs::InputManager::mousePos;

		camera->SetPosition(Vector3(-mousePos.x + camera->GetPosition().x, mousePos.y + camera->GetPosition().y, camera->GetPosition().z));
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
