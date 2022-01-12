#pragma once

#include <windows.h>
#include <windowsx.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <DirectXCollision.h>
#include "DDSTextureLoader.h"
#include "resource.h"
#include <iostream>

#include "structures.h"

#include <vector>

class CEntity;

struct Engine
{
	
	// Drawables.
	static std::vector<CEntity*> entities;
	
	template<class T>
	// Returns all entities of provided type that exist in the engine.
	static std::vector<T> GetEntityOfType()
	{
		std::vector<T> outputVector;

		for(CEntity& entity : entities)
		{
			if (typeof(entity) == T)
			{
				outputVector.emplace_back(entity);
			}
		}
		return outputVector;
	};

	template<class T>
	// Creates a entity, adds it to drawables and returns it back.
	static T* CreateEntity()
	{
		CEntity* temp = new T();
		entities.emplace_back(temp);
		return (T*)temp;
	}

	// Window and Instance.
	static HINSTANCE instanceHandle;
	static HWND windowHandle;
	static int windowWidth;
	static int windowHeight;

	// Direct3D.
	static D3D_DRIVER_TYPE driverType;
	static D3D_FEATURE_LEVEL featureLevel;
	static ID3D11Device* device;
	static ID3D11DeviceContext* deviceContext;
};