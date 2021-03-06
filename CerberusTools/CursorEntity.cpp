#include "CursorEntity.h"
#include "Cerberus/Core/Utility/DebugOutput/Debug.h"
#include "Cerberus/Core/Components\CTextRenderComponent.h"
#include <sstream>
#include "Cerberus\Core\Structs\CCamera.h"
#include "Cerberus/Core/Utility/Math/Math.h"
#include "Cerberus\Core\Utility\CameraManager\CameraManager.h"
#include "Cerberus/Core/Components/CAnimationSpriteComponent.h"

CursorEntity::CursorEntity()
{
	SetPosition(0, 0, -100);

	sprite = AddComponent<CAnimationSpriteComponent>(NAME_OF(sprite));
	sprite->LoadTextureWIC("Resources\\cursorSS.png");
	sprite->SetRenderRect(XMUINT2(16, 16));
	sprite->SetSpriteSize(XMUINT2(64, 64));
	sprite->SetAnimationRectSize(XMUINT2(2, 1));
	sprite->SetAnimationSpeed(2);
	sprite->SetIsUI(true);

	text = AddComponent<CTextRenderComponent>(NAME_OF(text));
	text->SetJustification(TextJustification::Center);
	text->SetPosition(0, -48, 0);
	text->SetIsUI(true);
}

void CursorEntity::Update(float deltaTime)
{
	CCameraComponent* camera = CameraManager::GetRenderingCamera();
	timeElapsed += deltaTime;

	unsigned char row = 0;
	if (InputManager::IsMouseButtonPressed(InputManager::RButton))
		row = 2;
	else if (InputManager::IsMouseButtonPressed(InputManager::LButton))
		row = 1;

	sprite->SetAnimationRectPosition(XMUINT2(0, row));

	SetPosition(Vector3(InputManager::mousePos.x - Engine::windowWidth * 0.5f, -InputManager::mousePos.y + Engine::windowHeight * 0.5f, GetPosition().z));

	XMFLOAT3 screenVec = XMFLOAT3(GetPosition().x, GetPosition().y, GetPosition().z);
	screenVec = Math::FromScreenToWorld(screenVec);

	std::stringstream ss;
	ss << "X:" << round(screenVec.x) << " Y:" << round(screenVec.y);
	text->SetText(ss.str());

	if (InputManager::IsMouseButtonPressed(InputManager::MButton))
	{
		if (!mouseRHeld)
		{
			mouseRHeld = true;
			mouseOffset = InputManager::mousePos;
		}

		Vector3 mousePos = (InputManager::mousePos - mouseOffset) / camera->GetZoomLevel();
		mouseOffset = InputManager::mousePos;

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
