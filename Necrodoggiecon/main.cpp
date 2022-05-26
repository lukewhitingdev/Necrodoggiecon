#include "Cerberus\Core\Engine.h"
#include <Cerberus\Core\Environment\CWorld.h>
#include "Necrodoggiecon/CWorld_Menu.h"
#include "Necrodoggiecon/CWorld_Game.h"
#include "Necrodoggiecon\Game\CPlayer.h"
#include <Necrodoggiecon\Game\TestUI.h>
#include <Necrodoggiecon\Game\CursorEntity.h>
#include <Necrodoggiecon\Game\PlayerController.h>
#include <Necrodoggiecon\Game\PlayerCharacter.h>>
#include "Necrodoggiecon\Game\AI\CAIController.h"
#include <Cerberus/Core/Structs/CCamera.h>
#include <Cerberus/Core/Utility/CWorldManager.h>
#include <Cerberus\Core\Components\CCameraComponent.h>
#include "Cerberus/Core/Utility/CameraManager/CameraManager.h"
#include "Necrodoggiecon/Game/AI/GruntEnemy.h"
#include "Necrodoggiecon/Game/AI/DogEnemy.h"
#include "Necrodoggiecon/Game/AI/AlarmEnemy.h"
#include <weaponUI.h>
#include <Necrodoggiecon\Game\CInteractable.h>
#include <Game/WeaponPickup.h>
#include <Weapons/Melee/Dagger.h>
#include <Weapons/Melee/Rapier.h>
#include <Weapons/Melee/Longsword.h>
#include <Weapons/Ranged/Crossbow.h>
#include <Weapons/Ranged/Fireball.h>
#include <Weapons/Ranged/MagicMissile.h>
#include "Necrodoggiecon/MainMenu.h"
#include "Necrodoggiecon/PauseMenu.h"
#include "Cerberus/Core/Utility/CUIManager.h"
#include <Necrodoggiecon/Game/DialogueHandler.h>
#include "Weapons/Pickup/InvisibilityScroll.h"
#include "Weapons/Pickup/ShieldScroll.h"

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

	//CInteractable* interactable = Engine::CreateEntity<CInteractable>();

	//interactable->SetPosition(-500, 0, 0);

	// Free Camera not locked to player.
	CCamera* freeCamera = Engine::CreateEntity<CCamera>();
	CCameraComponent* freeCameraComponent = freeCamera->AddComponent<CCameraComponent>(NAME_OF(freeCameraComponent));
	freeCameraComponent->SetAttachedToParent(false);
	CameraManager::AddCamera(freeCameraComponent);

	CameraManager::SetRenderingCamera(freeCameraComponent);

	CWorldManager::LoadWorld(new CWorld_Menu());


	

	

	CEntity* t = Engine::CreateEntity<weaponUI>();
	t->SetPosition(XMFLOAT3(0, 0, -90));
	t = Engine::CreateEntity<TestUI>();
	t->SetPosition(XMFLOAT3(0, 0, -100));
	t = Engine::CreateEntity<CursorEntity>();
	t->SetPosition(XMFLOAT3(0, 0, -110));



	/*Engine::CreateEntity<GruntEnemy>();
	Engine::CreateEntity<GruntEnemy>();
	Engine::CreateEntity<GruntEnemy>();
	Engine::CreateEntity<GruntEnemy>();
	Engine::CreateEntity<AlarmEnemy>();*/
	//controller->charOne = character1;

//	character1->SetPosition(Vector3(0, 0, 0));
	//controller->Possess(character1);
	//character1->shouldMove = true;
	//character1->colComponent->SetCollider(128.0f, 128.0f);

	std::vector<PlayerCharacter*> test = Engine::GetEntityOfType<PlayerCharacter>();

	
	//Engine::CreateEntity<WeaponPickup<Dagger>>();
	//Engine::CreateEntity<WeaponPickup<Rapier>>()->SetPosition(-100.0f, 0.0f, 0.0f);
	//Engine::CreateEntity<WeaponPickup<Longsword>>()->SetPosition(100.0f, 0.0f, 0.0f);
	//Engine::CreateEntity<WeaponPickup<Crossbow>>()->SetPosition(100.0f, 100.0f, 0.0f);
	//Engine::CreateEntity<WeaponPickup<Fireball>>()->SetPosition(0.0f, 100.0f, 0.0f);
	//Engine::CreateEntity<WeaponPickup<MagicMissile>>()->SetPosition(-100.0f, 100.0f, 0.0f);
	//Engine::CreateEntity<WeaponPickup<ShieldScroll>>()->SetPosition(800.0f, 400, 0.0f);
//	Engine::CreateEntity<WeaponPickup<InvisibilityScroll>>()->SetPosition(800.0f, 450, 0.0f);

	return 0;
}
