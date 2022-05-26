#include "CWorld_Menu.h"
#include "Cerberus/Core/Utility/CUIManager.h"
#include "Necrodoggiecon/MainMenu.h"
#include "Cerberus/Core/Components/CCameraComponent.h"
#include "Cerberus/Core/Structs/CCamera.h"
#include "Cerberus/Core/Utility/CameraManager/CameraManager.h"


void CWorld_Menu::SetupWorld()
{
	// Free Camera not locked to player.
	CCamera* freeCamera = Engine::CreateEntity<CCamera>();
	CCameraComponent* freeCameraComponent = freeCamera->AddComponent<CCameraComponent>(NAME_OF(freeCameraComponent));
	freeCameraComponent->SetAttachedToParent(false);
	CameraManager::AddCamera(freeCameraComponent);

	CameraManager::SetRenderingCamera(freeCameraComponent);

	CUIManager::AddCanvas(Engine::CreateEntity<MainMenu>(), "MainMenu");
}
