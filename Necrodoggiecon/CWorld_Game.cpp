#include "CWorld_Game.h"
#include <Necrodoggiecon\Game\PlayerController.h>
#include <Necrodoggiecon\Game\PlayerCharacter.h>
#include <Cerberus\Core\Components\CCameraComponent.h>
#include "Cerberus/Core/Utility/CameraManager/CameraManager.h"
#include <Cerberus/Core/Structs/CCamera.h>


CWorld_Game::CWorld_Game(int Slot)
{
	LoadWorld(Slot);
}

void CWorld_Game::SetupWorld()
{
	PlayerController* controller = Engine::CreateEntity<PlayerController>();
	PlayerCharacter* character1 = Engine::CreateEntity<PlayerCharacter>();

	// Locked Camera follows player.
	CCameraComponent* lockedCameraComponent = character1->AddComponent<CCameraComponent>();
	lockedCameraComponent->Initialize();
	lockedCameraComponent->SetAttachedToParent(true);

	CameraManager::AddCamera(lockedCameraComponent);

	CameraManager::SetRenderingCamera(lockedCameraComponent);

	controller->charOne = character1;

	character1->SetPosition(Vector3(StartPos.x, StartPos.y, 0) * (tileScale * tileScaleMultiplier) + Vector3(0, 0, -1));
	controller->Possess(character1);
	character1->shouldMove = true;
	character1->colComponent->SetCollider(128.0f, 128.0f);
}
