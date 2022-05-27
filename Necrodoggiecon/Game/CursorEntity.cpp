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
	SetIsUI(true);
	SetPosition(0, 0, -100);

	sprite = AddComponent<CAnimationSpriteComponent>(NAME_OF(sprite));
	sprite->LoadTextureWIC("Resources/Game/cursorSS.png");
	sprite->SetRenderRect(XMUINT2(16, 16));
	sprite->SetSpriteSize(XMUINT2(64, 64));
	sprite->SetAnimationRectSize(XMUINT2(2, 1));
	sprite->SetAnimationSpeed(2);
	sprite->SetIsUI(true);
}

void CursorEntity::Update(float deltaTime)
{
	CCameraComponent* camera = CameraManager::GetRenderingCamera();

	if(zoomLevel == 0 && camera != nullptr)
	{
		zoomLevel = CameraManager::GetRenderingCamera()->GetZoomLevel();
	}

	SetPosition(Vector3(InputManager::mousePos.x - Engine::windowWidth * 0.5f, -InputManager::mousePos.y + Engine::windowHeight * 0.5f, GetPosition().z));

	XMFLOAT3 screenVec = XMFLOAT3(GetPosition().x, GetPosition().y, GetPosition().z);
	screenVec = Math::FromScreenToWorld(screenVec);

	if (InputManager::IsMouseButtonPressed(InputManager::LButton))
	{
		if (!mouseLHeld)
		{
			mouseLHeld = true;
			sprite->SetAnimationRectPosition(XMUINT2(0, 1));
		}
	}
	else
	{
		if (mouseLHeld)
		{
			mouseLHeld = false;
			sprite->SetAnimationRectPosition(XMUINT2(0, 0));
		}
	}

	if(camera != nullptr)
	{
		if (InputManager::IsKeyPressedDown(InputManager::LShift))
		{
			camera->SetZoomLevel(zoomLevel * 0.5);
		}
		else
		{
			camera->SetZoomLevel(zoomLevel);
		}
	}
}

CursorEntity::~CursorEntity()
{

}
