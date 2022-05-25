//--------------------------------------------------------------------------------------
// File: main.cpp
//
// This application demonstrates animation using matrix transformations
//
// http://msdn.microsoft.com/en-us/library/windows/apps/ff729722.aspx
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#define _XM_NO_INTRINSICS_

#include "Cerberus/resource.h"
#include "Cerberus\Core\Engine.h"
#include "Cerberus\Core\Environment/CTile.h"
#include "Cerberus\Core\Environment/CWorld_Edit.h"
#include "Cerberus\Core\Structs\CCamera.h"
#include "Cerberus\Tools/CT_EditorMain.h"
#include "Cerberus/Core/Utility/Audio/AudioController.h"
#include "Cerberus/Core/Utility/EventSystem/EventSystem.h"
#include "Core/Components/CCameraComponent.h"
#include "Cerberus/Core/Utility/InputManager/InputManager.h"
#include "Cerberus/Core/Components/CCameraComponent.h"
#include "Cerberus\Core\Utility\CameraManager\CameraManager.h"
#include "Cerberus\Core\Utility\CWorldManager.h"
#include "Cerberus/Core/Utility/CUIManager.h"
#include <chrono>

XMMATRIX Engine::projMatrixUI = XMMatrixIdentity();

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT		InitWindow(HINSTANCE hInstance, int nCmdShow, WNDPROC wndProc);
HRESULT		InitDevice();
HRESULT		InitMesh();
HRESULT		InitWorld(int width, int height);
void		CleanupDevice();
void		Render();
void		Update(float deltaTime);
void		Load();
double CalculateDeltaTime(const unsigned short fpsCap = 0);

// Defines.
// Window and Instance.
HINSTANCE Engine::instanceHandle;
HWND Engine::windowHandle;
unsigned int Engine::windowWidth = 1280;
unsigned int Engine::windowHeight = 720;
bool resizeSwapChain = false;
bool fillState = true;
bool minimised = false;
double globalDeltaTime = 0.0;

//set to 0 for uncapped frames
const unsigned short maxFPS = 144;

std::chrono::high_resolution_clock::time_point tpOld;
std::chrono::high_resolution_clock::time_point tpNew;
double totalFrameTime = 0.0;
					   
// Direct3D.           
D3D_DRIVER_TYPE Engine::driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL Engine::featureLevel = D3D_FEATURE_LEVEL_11_0;
ID3D11Device* Engine::device;
ID3D11DeviceContext* Engine::deviceContext;
                      
//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
ID3D11VertexShader* vertexShader;
ID3D11PixelShader* pixelShader;
ID3D11PixelShader* pixelShaderSolid;
ID3D11InputLayout* vertexLayout;
ID3D11Buffer* constantBuffer;
IDXGISwapChain* swapChain;
ID3D11RenderTargetView* renderTargetView;
ID3D11Texture2D* depthStencil;
ID3D11DepthStencilView* depthStencilView;
ID3D11RasterizerState* fillRastState;
ID3D11RasterizerState* wireframeRastState;
ID3D11BlendState* blendState;
ID3D11DepthStencilState* opaqueDepthStencilState;
ID3D11DepthStencilState* translucentDepthStencilState;

DebugOutput* debugOutputUI;


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow, WNDPROC wndProc )
{
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof( WNDCLASSEX );
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = wndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIconW(hInstance, (LPCTSTR)IDI_ICON2);
	wcex.hCursor = LoadCursor( nullptr, IDC_ARROW );
	wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"Necrodoggiecon";
	wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_ICON2);
	if( !RegisterClassEx( &wcex ) )
		return E_FAIL;

	Engine::windowWidth = 1280;
	Engine::windowHeight = 720;

	// Create window
	Engine::instanceHandle = hInstance;
	RECT rc = { 0, 0, LONG(Engine::windowWidth), LONG(Engine::windowHeight) };

	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
	Engine::windowHandle = CreateWindow( L"Necrodoggiecon", L"Necrodoggiecon",
						   WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX,
						   CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
						   nullptr );
	if( !Engine::windowHandle)
		return E_FAIL;

	ShowWindow(Engine::windowHandle, nCmdShow);

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DCompile
//
// With VS 11, we could load up prebuilt .cso files instead...
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile( const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut )
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile( szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, 
		dwShaderFlags, 0, ppBlobOut, &pErrorBlob );
	if( FAILED(hr) )
	{
		if( pErrorBlob )
		{
			OutputDebugStringA( reinterpret_cast<const char*>( pErrorBlob->GetBufferPointer() ) );
			pErrorBlob->Release();
		}
		return hr;
	}
	if( pErrorBlob ) pErrorBlob->Release();

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice()
{
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect( Engine::windowHandle, &rc );
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE( driverTypes );

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

	for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
	{
		Engine::driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDevice( nullptr, Engine::driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
								D3D11_SDK_VERSION, &Engine::device, &Engine::featureLevel, &Engine::deviceContext );

		if ( hr == E_INVALIDARG )
		{
			// DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
			hr = D3D11CreateDevice( nullptr, Engine::driverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
									D3D11_SDK_VERSION, &Engine::device, &Engine::featureLevel, &Engine::deviceContext );
		}

		if( SUCCEEDED( hr ) )
			break;
	}
	if( FAILED( hr ) )
		return hr;

	// Obtain DXGI factory from device (since we used nullptr for pAdapter above)
	IDXGIFactory1* dxgiFactory = nullptr;
	{
		IDXGIDevice* dxgiDevice = nullptr;
		hr = Engine::device->QueryInterface( __uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice) );
		if (SUCCEEDED(hr))
		{
			IDXGIAdapter* adapter = nullptr;
			hr = dxgiDevice->GetAdapter(&adapter);
			if (SUCCEEDED(hr))
			{
				hr = adapter->GetParent( __uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory) );
				adapter->Release();
			}
			dxgiDevice->Release();
		}
	}
	if (FAILED(hr))
		return hr;

	// Create swap chain
	IDXGISwapChain1* swapChainTemp = nullptr;
	ID3D11Device1* deviceTemp = nullptr;
	ID3D11DeviceContext1* deviceContextTemp = nullptr;

	IDXGIFactory2* dxgiFactory2 = nullptr;
	hr = dxgiFactory->QueryInterface( __uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2) );
	if ( dxgiFactory2 )
	{
		// DirectX 11.1 or later
		hr = Engine::device->QueryInterface( __uuidof(ID3D11Device1), reinterpret_cast<void**>(&deviceTemp) );
		if (SUCCEEDED(hr))
		{
			(void) Engine::deviceContext->QueryInterface( __uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&deviceContextTemp) );
		}

		DXGI_SWAP_CHAIN_DESC1 sd = {};
		sd.Width = width;
		sd.Height = height;
		sd.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;//  DXGI_FORMAT_R16G16B16A16_FLOAT;////DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount = 1;

        hr = dxgiFactory2->CreateSwapChainForHwnd( Engine::device, Engine::windowHandle, &sd, nullptr, nullptr, &swapChainTemp);
        if (SUCCEEDED(hr))
        {
            hr = swapChainTemp->QueryInterface( __uuidof(IDXGISwapChain), reinterpret_cast<void**>(&swapChain) );
        }

        dxgiFactory2->Release();
    }
    else
    {
        // DirectX 11.0 systems
        DXGI_SWAP_CHAIN_DESC sd = {};
        sd.BufferCount = 1;
        sd.BufferDesc.Width = width;
        sd.BufferDesc.Height = height;
        //sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
        sd.BufferDesc.RefreshRate.Numerator = maxFPS;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = Engine::windowHandle;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;

        hr = dxgiFactory->CreateSwapChain( Engine::device, &sd, &swapChain );
    }

    swapChainTemp->Release();
    deviceTemp->Release();
    deviceContextTemp->Release();

    dxgiFactory->Release();

    if (FAILED(hr))
        return hr;

    // Create a render target view
    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = swapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), reinterpret_cast<void**>( &pBackBuffer ) );
    if( FAILED( hr ) )
        return hr;

    hr = Engine::device->CreateRenderTargetView( pBackBuffer, nullptr, &renderTargetView );
    pBackBuffer->Release();
    if( FAILED( hr ) )
        return hr;

    // Create depth stencil texture
    D3D11_TEXTURE2D_DESC descDepth = {};
    descDepth.Width = width;
    descDepth.Height = height;
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;
    hr = Engine::device->CreateTexture2D( &descDepth, nullptr, &depthStencil );
    if( FAILED( hr ) )
        return hr;

    // Create the depth stencil view
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;
    hr = Engine::device->CreateDepthStencilView( depthStencil, &descDSV, &depthStencilView );
    if( FAILED( hr ) )
        return hr;

    Engine::deviceContext->OMSetRenderTargets( 1, &renderTargetView, depthStencilView );

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    Engine::deviceContext->RSSetViewports( 1, &vp );

	D3D11_BLEND_DESC blend;
	blend.RenderTarget[0].BlendEnable = TRUE;
	blend.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blend.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blend.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blend.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blend.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blend.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blend.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	blend.IndependentBlendEnable = false;
	blend.AlphaToCoverageEnable = false;
	hr = Engine::device->CreateBlendState(&blend, &blendState);

	if (FAILED(hr))
		return hr;

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = FALSE;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;
	hr = Engine::device->CreateDepthStencilState(&depthStencilDesc, &opaqueDepthStencilState);

	if (FAILED(hr))
		return hr;

	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

	hr = Engine::device->CreateDepthStencilState(&depthStencilDesc, &translucentDepthStencilState);

	if (FAILED(hr))
		return hr;

	Engine::deviceContext->OMSetDepthStencilState(opaqueDepthStencilState, 0);

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	UINT sampleMask = 0xffffffff;

	Engine::deviceContext->OMSetBlendState(blendState, blendFactor, sampleMask);

	D3D11_RASTERIZER_DESC fillDSC = {};
	fillDSC.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	fillDSC.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	Engine::device->CreateRasterizerState(&fillDSC, &fillRastState);

	D3D11_RASTERIZER_DESC wireframeDSC = {};
	wireframeDSC.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	wireframeDSC.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
	Engine::device->CreateRasterizerState(&wireframeDSC, &wireframeRastState);

	Engine::deviceContext->RSSetState(fillRastState);
	//Engine::deviceContext->RSSetState(wireframeRastState);

	hr = InitMesh();
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"Failed to initialise mesh.", L"Error", MB_OK);
		return hr;
	}

	hr = InitWorld(width, height);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"Failed to initialise world.", L"Error", MB_OK);
		return hr;
	}

	if (FAILED(hr))
		return hr;

	return S_OK;
}

// ***************************************************************************************
// InitMesh
// ***************************************************************************************
HRESULT	InitMesh()
{
	// Compile the vertex shader
	ID3DBlob* pVSBlob = nullptr;
	HRESULT hr = CompileShaderFromFile(L"Resources/Engine/Shaders/shader.fx", "VS", "vs_4_0", &pVSBlob);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the vertex shader
	hr = Engine::device->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &vertexShader);
	if (FAILED(hr))
	{
		pVSBlob->Release();
		return hr;
	}

	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	hr = Engine::device->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(), &vertexLayout);
	pVSBlob->Release();
	if (FAILED(hr))
		return hr;

	// Set the input layout
	Engine::deviceContext->IASetInputLayout(vertexLayout);

	// Compile the pixel shader
	ID3DBlob* pPSBlob = nullptr;
	hr = CompileShaderFromFile(L"Resources/Engine/Shaders/shader.fx", "PS", "ps_4_0", &pPSBlob);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the pixel shader
	hr = Engine::device->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &pixelShader);
	pPSBlob->Release();
	if (FAILED(hr))
		return hr;

	hr = CompileShaderFromFile(L"Resources/Engine/Shaders/shader.fx", "PSSolid", "ps_4_0", &pPSBlob);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the pixel shader
	hr = Engine::device->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &pixelShaderSolid);
	pPSBlob->Release();
	if (FAILED(hr))
		return hr;

	// Create the constant buffer
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = Engine::device->CreateBuffer(&bd, nullptr, &constantBuffer);
	if (FAILED(hr))
		return hr;

	return hr;
}

// ***************************************************************************************
// InitWorld
// ***************************************************************************************
HRESULT	InitWorld(int width, int height)
{
	UNREFERENCED_PARAMETER(width);
	UNREFERENCED_PARAMETER(height);

	Engine::projMatrixUI = XMMatrixOrthographicLH(float(Engine::windowWidth), float(Engine::windowHeight), -1000.0f, 1000.0f);

	return S_OK;
}

//https://docs.microsoft.com/en-us/windows/win32/direct3ddxgi/d3d10-graphics-programming-guide-dxgi#handling-window-resizing
HRESULT ResizeSwapChain(XMUINT2 newSize)
{
	Engine::windowWidth = newSize.x;
	Engine::windowHeight = newSize.y;

	HRESULT hr = S_OK;
	if (swapChain)
	{
		Engine::deviceContext->OMSetRenderTargets(0, 0, 0);

		// Release all outstanding references to the swap chain's buffers.
		renderTargetView->Release();

		// Preserve the existing buffer count and format.
		// Automatically choose the width and height to match the client rect for HWNDs.
		hr = swapChain->ResizeBuffers(0, Engine::windowWidth, Engine::windowHeight, DXGI_FORMAT_UNKNOWN, 0);

		if (FAILED(hr))
			return hr;

		// Get buffer and create a render-target-view.
		ID3D11Texture2D* pBuffer;
		hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
			(void**)&pBuffer);
		
		if (FAILED(hr))
			return hr;

		hr = Engine::device->CreateRenderTargetView(pBuffer, NULL,
			&renderTargetView);

		if (FAILED(hr))
			return hr;

		pBuffer->Release();

		Engine::deviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);

		if(depthStencil) depthStencil->Release();
		if(depthStencilView) depthStencilView->Release();

		// Create depth stencil texture
		D3D11_TEXTURE2D_DESC descDepth = {};
		descDepth.Width = newSize.x;
		descDepth.Height = newSize.y;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;
		hr = Engine::device->CreateTexture2D(&descDepth, nullptr, &depthStencil);
		if (FAILED(hr))
			return hr;

		// Create the depth stencil view
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
		descDSV.Format = descDepth.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;
		hr = Engine::device->CreateDepthStencilView(depthStencil, &descDSV, &depthStencilView);
		if (FAILED(hr))
			return hr;

		Engine::deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

		// Set up the viewport.
		D3D11_VIEWPORT vp;
		vp.Width = (FLOAT)newSize.x;
		vp.Height = (FLOAT)newSize.y;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		Engine::deviceContext->RSSetViewports(1, &vp);

		InitWorld(newSize.x, newSize.y);

		CameraManager::GetRenderingCamera()->UpdateProj();
	}

	return hr;
}

#include <map>

//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
	while (EntityManager::GetEntitiesVector()->size() > 0)
	{
		CEntity* e = EntityManager::GetEntitiesVector()->at(0);
		EntityManager::RemoveEntity(e);
		delete e;
	}

	// Remove any bound render target or depth/stencil buffer
	ID3D11RenderTargetView* nullViews[] = { nullptr };
	Engine::deviceContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);

	if( Engine::deviceContext ) Engine::deviceContext->ClearState();
	Engine::deviceContext->Flush();

    if (vertexLayout) vertexLayout->Release();
    if( constantBuffer ) constantBuffer->Release();
    if (vertexShader) vertexShader ->Release();
    if( pixelShader ) pixelShader->Release();
    if( pixelShaderSolid ) pixelShaderSolid->Release();
    if( depthStencil ) depthStencil->Release();
    if( depthStencilView ) depthStencilView->Release();
    if( renderTargetView ) renderTargetView->Release();
    if( swapChain ) swapChain->Release();
    if( Engine::deviceContext ) Engine::deviceContext->Release();
	if (fillRastState) fillRastState->Release();
	if (wireframeRastState) wireframeRastState->Release();
	if (blendState) blendState->Release();
	if (opaqueDepthStencilState) opaqueDepthStencilState->Release();
	if (translucentDepthStencilState) translucentDepthStencilState->Release();

	ID3D11Debug* debugDevice = nullptr;
	Engine::device->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugDevice));

	if (Engine::device) Engine::device->Release();

	// handy for finding dx memory leaks
	if(debugDevice != nullptr)
	{
		debugDevice->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);

		if (debugDevice)
			debugDevice->Release();
	}

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
}

double CalculateDeltaTime(const unsigned short fpsCap)
{
	tpNew = std::chrono::high_resolution_clock::now();
	double deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(tpNew - tpOld).count();
	tpOld = tpNew;

	const double FPSMAX = 1.0 / double(fpsCap);
	totalFrameTime += deltaTime;

	if (totalFrameTime > FPSMAX || fpsCap == 0)
	{
		deltaTime = totalFrameTime;
		totalFrameTime = 0.0;
		return deltaTime;
	}
	else
	{
		return -8008135.0;	//Special number for telling the program to skip the frame
	}
}

void Engine::DestroyEntity(CEntity* targetEntity)
{
	EntityManager::RemoveEntity(targetEntity);

	delete targetEntity;
}

// Starts the engine.
bool Engine::Start(HINSTANCE hInstance, int nCmdShow, WNDPROC wndProc)
{
	srand((unsigned int)time(0));

	if (FAILED(InitWindow(hInstance, nCmdShow, wndProc)))
		return false;

	if (FAILED(InitDevice()))
	{
		CleanupDevice();
		return false;
	}

	// Init ImGUI.
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	ImGui::StyleColorsDark();                                   // Style colors dark

	ImGui_ImplWin32_Init(Engine::windowHandle);
	ImGui_ImplDX11_Init(Engine::device, Engine::deviceContext);

	tpOld = std::chrono::high_resolution_clock::now();

	return true;
}

void Engine::RenderUpdateLoop()
{
	if (!minimised)
	{
		double t = CalculateDeltaTime(maxFPS);
		if (t == -8008135.0)
			return;

		globalDeltaTime = t;

		Update((float)globalDeltaTime);
		Render();
	}
	else
	{
		Sleep(64);
	}
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT Engine::ReadMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CCameraComponent* camera = CameraManager::GetRenderingCamera();

	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return false;

	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_MOUSEMOVE:
	{
		InputManager::mousePos.x = float(GET_X_LPARAM(lParam));
		InputManager::mousePos.y = float(GET_Y_LPARAM(lParam));
		break;
	}

	case WM_KEYDOWN:
		if (wParam == VK_F1)
		{
			if (fillState)
				Engine::deviceContext->RSSetState(wireframeRastState);
			else
				Engine::deviceContext->RSSetState(fillRastState);

			fillState = !fillState;
			break;
		}
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(1);
			break;
		}
		break;
	case WM_KEYUP:

		break;

		//TEMP
	case WM_MOUSEWHEEL:
		camera->SetZoomLevel(float(camera->GetZoomLevel() + GET_WHEEL_DELTA_WPARAM(wParam) * camera->GetZoomLevel() * 0.001f));
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_SIZE:
		if (Engine::deviceContext != NULL)
		{
			resizeSwapChain = true;
			Engine::windowWidth = LOWORD(lParam);
			Engine::windowHeight = HIWORD(lParam);
		}

		if (wParam == SIZE_MINIMIZED)
			minimised = true;
		else
			minimised = false;
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void Engine::Stop()
{
	CleanupDevice();
}

void Update(float deltaTime)
{
	for (size_t i = 0; i < EntityManager::GetEntitiesVector()->size(); i++)
	{
		CEntity* e = EntityManager::GetEntitiesVector()->at(i);
		if (!e->GetShouldUpdate())
			continue;
		
		for (auto& f : e->GetAllComponents())
		{
			if (!f->GetShouldUpdate())
				continue;

			f->Update(deltaTime);
		}

		e->Update(deltaTime);
	}

	for (size_t i = 0; i < EntityManager::GetEntitiesVector()->size(); i++)
	{
		CEntity* e = EntityManager::GetEntitiesVector()->at(i);
		if (e->GetShouldMove())
		{
			for (size_t j = 0; j < EntityManager::GetEntitiesVector()->size(); j++)
			{
				CEntity* currentEntity = EntityManager::GetEntitiesVector()->at(j);

				if (e != currentEntity && currentEntity->colComponent != nullptr)
				{
					//If it can move, check the collisions and it is a different entity, do collision stuff
					if (e->colComponent->IsColliding(currentEntity->colComponent))
					{
						e->HasCollided(currentEntity->colComponent);
						currentEntity->HasCollided(e->colComponent);
					}
				}
			}
		}
	}

	AudioController::Update(deltaTime);
}

//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render()
{
	CCameraComponent* camera = CameraManager::GetRenderingCamera();

	// Cant render without a rendering camera.
	if(camera == nullptr)
	{
		return;
	}

	if (resizeSwapChain)
	{
		ResizeSwapChain(XMUINT2(Engine::windowWidth, Engine::windowHeight));
		resizeSwapChain = false;
	}

    // Clear the back buffer
    Engine::deviceContext->ClearRenderTargetView( renderTargetView, Colors::MidnightBlue );

    // Clear the depth buffer to 1.0 (max depth)
    Engine::deviceContext->ClearDepthStencilView( depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );

	Engine::deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
	Engine::deviceContext->PSSetConstantBuffers(0, 1, &constantBuffer);

	Engine::deviceContext->VSSetShader(vertexShader, nullptr, 0);

	if (fillState)
		Engine::deviceContext->PSSetShader(pixelShader, nullptr, 0);
	else
		Engine::deviceContext->PSSetShader(pixelShaderSolid, nullptr, 0);


	XMFLOAT4X4 mat = camera->GetViewMatrix();
	XMMATRIX viewMat = XMMatrixTranspose(XMLoadFloat4x4(&mat));

	mat = camera->GetProjectionMatrix();
	XMMATRIX projMat = XMMatrixTranspose(XMLoadFloat4x4(&mat));

	// Set primitive topology
	Engine::deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	for (size_t i = 0; i < EntityManager::GetOpaqueCompsVector()->size(); i++)
	{
		CComponent* c = EntityManager::GetOpaqueCompsVector()->at(i);
		CEntity* e = c->GetParent();
		if (e->GetVisible())
		{
			XMFLOAT4X4 entTransform = e->GetTransform();

			if (c->GetShouldDraw())
			{
				ConstantBuffer cb1;
				cb1.mView = viewMat;
				cb1.mProjection = projMat;

				c->Draw(Engine::deviceContext, entTransform, cb1, constantBuffer);
			}
		}
	}

	EntityManager::SortTranslucentComponents();

	Engine::deviceContext->OMSetDepthStencilState(translucentDepthStencilState, 0);

	for (size_t i = 0; i < EntityManager::GetTranslucentCompsVector()->size(); i++)
	{
		CComponent* c = EntityManager::GetTranslucentCompsVector()->at(i);
		CEntity* e = c->GetParent();
		if (e->GetVisible())
		{
			XMFLOAT4X4 entTransform = e->GetTransform();

			if (c->GetShouldDraw())
			{
				ConstantBuffer cb1;
				cb1.mView = viewMat;
				cb1.mProjection = projMat;

				c->Draw(Engine::deviceContext, entTransform, cb1, constantBuffer);
			}
		}
	}

	Engine::deviceContext->OMSetDepthStencilState(opaqueDepthStencilState, 0);

	// Render ImGUI.
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// Do UI.
	Debug::getOutput()->render();
	if (CWorldManager::GetEditorWorld() != nullptr)CWorldManager::GetEditorWorld()->UpdateEditorViewport();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // Present our back buffer to our front buffer
    swapChain->Present( 0, 0 );
}

