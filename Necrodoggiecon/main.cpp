#include "Cerberus\Core\Engine.h"
#include "Cerberus\Core\Environment\CWorld.h"
#include "Necrodoggiecon/CWorld_Menu.h"
#include "Necrodoggiecon/CWorld_Game.h"
#include "Cerberus/Core/Utility/CWorldManager.h"
#include "Game/SoundManager.h"
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
	#ifdef _DEBUG
		Debug::SetLogging(true);
		Debug::SetVisibility(true);
	#endif

	#ifndef _DEBUG
			Debug::SetLogging(false);
			Debug::SetVisibility(false);
	#endif

	SoundManager::Initialise();

	CWorldManager::LoadWorld(new CWorld_Menu());
	return 0;
}
