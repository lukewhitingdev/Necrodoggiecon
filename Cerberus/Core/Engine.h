#pragma once

#include <windows.h>
#include <windowsx.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <DirectXCollision.h>
#include <vector>
#include <iostream>

#include "Cerberus\Dependencies\Microsoft\DDSTextureLoader.h"

#pragma warning(push)
//Disabled Warnings that reside in external libraries.
#pragma warning( disable : 26812 )
#include "Cerberus\Dependencies\Microsoft/WICTextureLoader.h"
#pragma warning(pop)


#include "Cerberus\Dependencies\IMGUI/imgui.h"
#include "Cerberus\Dependencies\IMGUI/imgui_impl_dx11.h"
#include "Cerberus\Dependencies\IMGUI/imgui_impl_win32.h"

#include "Cerberus/Core/Utility/DebugOutput/Debug.h"
#include "Cerberus/Core/Utility/InputManager/InputManager.h"

#include "Cerberus\Core\Structs\structures.h"
#include "Cerberus\Resource.h"

#define PI 3.14159
#define DEG2RAD PI / 180
#define RAD2DEG 180 / PI

class CEntity;

struct Engine
{
	static bool Start(HINSTANCE hInstance, int nCmdShow, WNDPROC wndProc);

	static void RenderUpdateLoop();

	static LRESULT ReadMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static void Stop();

	// Drawables.
	static std::vector<CEntity*> entities;	//Needs to be changed to CObject instead
	
	template<class T>
	// Returns all entities of provided type that exist in the engine.
	static std::vector<T*> GetEntityOfType() 
	{
		std::vector<T*> outputVector;

		size_t vectorSize = entities.size();
		for (size_t i = 0; i < vectorSize; i++)
		{
			T* entity = (T*)entities[i];
			const char* evaluationEntity = typeid(*entity).name();
			const char* searchEntity = typeid(T).name();
			if (evaluationEntity == searchEntity)
				outputVector.emplace_back(entity);
		}
		return outputVector;
	};

	static void DestroyEntity(CEntity* targetEntity);

	template<class T>
	// Creates a entity, adds it to drawables and returns it back.
	static T* CreateEntity() 
	{
		CEntity* temp = new T();
		entities.emplace_back(temp);
		return (T*)temp;
	};

	// Window and Instance.
	static HINSTANCE instanceHandle;
	static HWND windowHandle;
	static unsigned int windowWidth;
	static unsigned int windowHeight;

	// Direct3D.
	static D3D_DRIVER_TYPE driverType;
	static D3D_FEATURE_LEVEL featureLevel;
	static ID3D11Device* device;
	static ID3D11DeviceContext* deviceContext;

	static class CCamera camera;
	static XMMATRIX projMatrixUI;
};