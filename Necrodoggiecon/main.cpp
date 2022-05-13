#include "Cerberus\Core\Engine.h"
#include <Cerberus\Core\Environment\CWorld.h>
#include "Necrodoggiecon\Game\CPlayer.h"
#include <Necrodoggiecon\Game\TestUI.h>
#include <Necrodoggiecon\Game\CursorEntity.h>
#include <Necrodoggiecon\Game\PlayerController.h>
#include <Necrodoggiecon\Game\PlayerCharacter.h>
#include <Necrodoggiecon\Game\ItemDatabase.h>
#include <Necrodoggiecon\Game\AI\CAIController.h>
#include <Cerberus/Core/Structs/CCamera.h>
#include <Cerberus/Core/Utility/CWorldManager.h>
#include <Cerberus\Core\Components\CCameraComponent.h>
#include "Cerberus/Core/Utility/CameraManager/CameraManager.h"
#include <weaponUI.h>

/*

TODO:
Probs make Header files that hold other functionality of engine, Like Audio.h having all static audio functions etc.

*/

int Start();

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Engine Start
	Engine::Start(hInstance, nCmdShow, WndProc);

	Start();

	// Main message loop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Engine Update / Render
			Engine::RenderUpdateLoop();
		}
	}

	// Engine Cleanup / Destroy
	Engine::Stop();

	return (int)msg.wParam;
}

//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Engine WndProc Hook.
	return Engine::ReadMessage(hWnd, message, wParam, lParam);
}

// Called once at the start of the application run.
int Start() 
{	
	// Free Camera not locked to player.
	CCamera* freeCamera = Engine::CreateEntity<CCamera>();
	CCameraComponent* freeCameraComponent = freeCamera->AddComponent<CCameraComponent>();
	freeCameraComponent->Initialize();
	freeCameraComponent->SetAttachedToParent(false);

	CameraManager::AddCamera(freeCameraComponent);

	CWorldManager::LoadWorld(0, false);

	PlayerController* controller = Engine::CreateEntity<PlayerController>();
	PlayerCharacter* character1 = Engine::CreateEntity<PlayerCharacter>();

	// Locked Camera follows player.
	CCameraComponent* lockedCameraComponent = character1->AddComponent<CCameraComponent>();
	lockedCameraComponent->Initialize();
	lockedCameraComponent->SetAttachedToParent(true);

	CameraManager::AddCamera(lockedCameraComponent);

	CameraManager::SetRenderingCamera(lockedCameraComponent);

	Engine::CreateEntity<weaponUI>();
	Engine::CreateEntity<TestUI>();
	Engine::CreateEntity<CursorEntity>();

	CDroppedItem* droppedItem = ItemDatabase::CreateDroppedItemFromID(0);

	//character1->SetPosition(Vector3((float(rand() % Engine::windowWidth) - Engine::windowWidth / 2), (float(rand() % Engine::windowHeight) - Engine::windowHeight / 2), 0));
	character1->droppedItem = droppedItem;

	controller->charOne = character1;

	character1->SetPosition(Vector3(0, 0, 0));
	controller->Possess(character1);
	character1->shouldMove = true;
	character1->colComponent->SetCollider(128.0f, 128.0f);

	Engine::CreateEntity<CAIController>();

	std::vector<PlayerCharacter*> test = Engine::GetEntityOfType<PlayerCharacter>();

	return 0;
}
