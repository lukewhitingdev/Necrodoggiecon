#include <iostream>
#include "Cerberus\Core\Engine.h"
#include <Cerberus\Core\Environment\CWorld.h>
#include "CerberusTools/CursorEntity.h"
#include <Cerberus/Core/Utility/CWorldManager.h>
#include "Cerberus/Core/Utility/CameraManager/CameraManager.h"
#include "Cerberus/Core/Structs/CCamera.h"


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
{// Free Camera not locked to player.
	CCamera* freeCamera = Engine::CreateEntity<CCamera>();
	CCameraComponent* freeCameraComponent = freeCamera->AddComponent<CCameraComponent>();
	freeCameraComponent->SetAttachedToParent(false);
	freeCameraComponent->SetParent(freeCamera);
	CameraManager::SetRenderingCamera(freeCameraComponent);

	CWorldManager::LoadWorld(0, true);
	Engine::CreateEntity<CursorEntity>();

	return 0;
}
