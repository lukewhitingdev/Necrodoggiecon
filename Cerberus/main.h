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

#include "DrawableGameObject.h"
#include "structures.h"

#include <vector>

using namespace std;


struct Engine
{
	
	// Drawables.
	vector<DrawableGameObject*> vecDrawables;
	
	template<class T>
	// Returns all entities of provided type that exist in the engine.
	static vector<T> GetEntityOfType() 
	{
		std::vector<T> outputVector;

		for(DrawableGameObject& entity : vecDrawables)
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
		DrawableGameObject* temp = new T();
		vecDrawables.emplace_back(temp);
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
	static IDXGISwapChain* swapChain;
	static ID3D11RenderTargetView* renderTargetView;
	static ID3D11Texture2D* depthStencil;
	static ID3D11DepthStencilView* depthStencilView;

	// Shaders.
	static ID3D11VertexShader* vertexShader;
	static ID3D11PixelShader* pixelShader;
	static ID3D11InputLayout* vertexLayout;
	static ID3D11Buffer* constantBuffer;
	static ID3D11Buffer* lightConstantBuffer;

	// Matrices.
	static XMMATRIX viewMatrix;
	static XMMATRIX projectionMatrix;
};

