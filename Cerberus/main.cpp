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

#include "Engine.h"
#include "Core/testClass.h"
#include "CTile.h"
#include "CWorld.h"

std::vector<CEntity*> Engine::entities = std::vector<CEntity*>();

DirectX::XMFLOAT4 g_EyePosition(0.0f, 0.0f, 3.0f, 1.0f);

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT		InitWindow(HINSTANCE hInstance, int nCmdShow);
HRESULT		InitDevice();
HRESULT		InitMesh();
HRESULT		InitWorld(int width, int height);
void		CleanupDevice();
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void		Render();
void		Update(float deltaTime);
void		Load();
float calculateDeltaTime();

// Defines.
// Window and Instance.
HINSTANCE Engine::instanceHandle;
HWND Engine::windowHandle;
int Engine::windowWidth = 1280;
int Engine::windowHeight = 720;
					   
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
ID3D11InputLayout* vertexLayout;
ID3D11Buffer* constantBuffer;
XMMATRIX viewMatrix;
XMMATRIX projectionMatrix;
IDXGISwapChain* swapChain;
ID3D11RenderTargetView* renderTargetView;
ID3D11Texture2D* depthStencil;
ID3D11DepthStencilView* depthStencilView;
ID3D11RasterizerState* fillRastState;
ID3D11RasterizerState* wireframeRastState;

DebugOutput* debugOutputUI;

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow )
{
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	srand(time(0));

	if( FAILED( InitWindow( hInstance, nCmdShow ) ) )
		return 0;

	if( FAILED( InitDevice() ) )
	{
		CleanupDevice();
		return 0;
	}

	// Init ImGUI.
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	ImGui::StyleColorsDark();                                   // Style colors dark

	ImGui_ImplWin32_Init(Engine::windowHandle);
	ImGui_ImplDX11_Init(Engine::device, Engine::deviceContext);

	Load();

	// Main message loop
	MSG msg = {0};
	while( WM_QUIT != msg.message )
	{
		if( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			float t = calculateDeltaTime(); // capped at 60 fps
			if (t == 0.0f)
				continue;

			Update(t);
			Render();
		}
	}

	CleanupDevice();

	return ( int )msg.wParam;
}

//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow )
{
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof( WNDCLASSEX );
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon( hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
	wcex.hCursor = LoadCursor( nullptr, IDC_ARROW );
	wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"Necrodoggiecon";
	wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
	if( !RegisterClassEx( &wcex ) )
		return E_FAIL;

	// Create window
	Engine::instanceHandle = hInstance;
	RECT rc = { 0, 0, 1280, 720 };

	Engine::windowWidth = 1280;
	Engine::windowHeight = 720;

	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
	Engine::windowHandle = CreateWindow( L"Necrodoggiecon", L"Necrodoggiecon",
						   WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
						   CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
						   nullptr );
	if( !Engine::windowHandle)
		return E_FAIL;

	ShowWindow(Engine::windowHandle, nCmdShow);

	return S_OK;
}

void Load()
{
	for (int i = 0; i < 25; i++)
	{
		TestClass* myClass = Engine::CreateEntity<TestClass>();
		myClass->SetPosition(Vector3((float(rand() % Engine::windowWidth) - Engine::windowWidth / 2), (float(rand() % Engine::windowHeight) - Engine::windowHeight / 2), 0));
	}

	//CWorld* World = new CWorld(0);
	//World->LoadWorld(0);
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
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
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

    // Note this tutorial doesn't handle full-screen swapchains so we block the ALT+ENTER shortcut
    dxgiFactory->MakeWindowAssociation( Engine::windowHandle, DXGI_MWA_NO_ALT_ENTER );

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

	//for (auto& e : Engine::entities)
	//    e->components;

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
	HRESULT hr = CompileShaderFromFile(L"shader.fx", "VS", "vs_4_0", &pVSBlob);
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
	hr = CompileShaderFromFile(L"shader.fx", "PS", "ps_4_0", &pPSBlob);
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
HRESULT		InitWorld(int width, int height)
{
	// Initialize the view matrix
	XMVECTOR Eye = XMLoadFloat4(&g_EyePosition);
	XMVECTOR At = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	viewMatrix = XMMatrixLookAtLH(Eye, At, Up);

	const float viewScaler = 1;

	// Initialize the projection matrix
	projectionMatrix = XMMatrixOrthographicLH(width / viewScaler, height / viewScaler, 0.01f, 100.0f);

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
	for (auto& e : Engine::entities)
		delete e;

	Engine::entities.clear();

	// Remove any bound render target or depth/stencil buffer
	ID3D11RenderTargetView* nullViews[] = { nullptr };
	Engine::deviceContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);

	if( Engine::deviceContext ) Engine::deviceContext->ClearState();
	Engine::deviceContext->Flush();

    if (vertexLayout) vertexLayout->Release();
    if( constantBuffer ) constantBuffer->Release();
    if (vertexShader) vertexShader ->Release();
    if( pixelShader ) pixelShader->Release();
    if( depthStencil ) depthStencil->Release();
    if( depthStencilView ) depthStencilView->Release();
    if( renderTargetView ) renderTargetView->Release();
    if( swapChain ) swapChain->Release();
    if( Engine::deviceContext ) Engine::deviceContext->Release();
	if (fillRastState) fillRastState->Release();
	if (wireframeRastState) wireframeRastState->Release();

	ID3D11Debug* debugDevice = nullptr;
	Engine::device->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugDevice));

	if (Engine::device) Engine::device->Release();

	// handy for finding dx memory leaks
	debugDevice->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);

	if (debugDevice)
		debugDevice->Release();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{

	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;

	PAINTSTRUCT ps;
	HDC hdc;

	switch( message )
	{
	case WM_LBUTTONDOWN:
	{
		//int xPos = GET_X_LPARAM(lParam);
		//int yPos = GET_Y_LPARAM(lParam);
		break;
	}
	case WM_PAINT:
		hdc = BeginPaint( hWnd, &ps );
		EndPaint( hWnd, &ps );
		break;

	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;

		// Note that this tutorial does not handle resizing (WM_SIZE) requests,
		// so we created the window without the resize border.

	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}

	return 0;
}

float calculateDeltaTime()
{
	// Update our time
	static float deltaTime = 0.0f;
	static ULONGLONG timeStart = 0;
	ULONGLONG timeCur = GetTickCount64();
	if (timeStart == 0)
		timeStart = timeCur;
	deltaTime = (timeCur - timeStart) / 1000.0f;
	timeStart = timeCur;

	float FPS60 = 1.0f / 60.0f;
	static float cummulativeTime = 0;

	// cap the framerate at 60 fps 
	cummulativeTime += deltaTime;
	if (cummulativeTime >= FPS60) {
		cummulativeTime = cummulativeTime - FPS60;
	}
	else {
		return 0;
	}

	return deltaTime;
}

void Update(float deltaTime)
{
	for (auto& e : Engine::entities)
		if(e->shouldUpdate)
		{
			for (auto& f : e->components)
				if(f->shouldUpdate)
					f->Update(deltaTime);

			e->Update(deltaTime);
		}
}

//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render()
{
    // Clear the back buffer
    Engine::deviceContext->ClearRenderTargetView( renderTargetView, Colors::MidnightBlue );

    // Clear the depth buffer to 1.0 (max depth)
    Engine::deviceContext->ClearDepthStencilView( depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );

	for (auto& e : Engine::entities)
	{
		//Maybe should have a visible bool for each entity

		XMFLOAT4X4 entWorld = e->GetTransform();
		XMMATRIX mGO = XMLoadFloat4x4(&entWorld);

		for (auto& f : e->components)
			if(f->shouldDraw)
			{
				// get the game object world transform
				XMFLOAT4X4 compWorld = f->GetTransform();
				XMMATRIX mGO2 = XMLoadFloat4x4(&compWorld) * mGO;

				// store this and the view / projection in a constant buffer for the vertex shader to use
				ConstantBuffer cb1;
				cb1.mWorld = XMMatrixTranspose(mGO2);
				cb1.mView = XMMatrixTranspose(viewMatrix);
				cb1.mProjection = XMMatrixTranspose(projectionMatrix);
				cb1.vOutputColor = XMFLOAT4(0, 0, 0, 0);
				Engine::deviceContext->UpdateSubresource(constantBuffer, 0, nullptr, &cb1, 0, 0);

				Engine::deviceContext->VSSetShader(vertexShader, nullptr, 0);
				Engine::deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);

				Engine::deviceContext->PSSetShader(pixelShader, nullptr, 0);

				f->Draw(Engine::deviceContext);
			}
	}

	// Render ImGUI.
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// Do UI.
	Debug::getOutput()->render();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // Present our back buffer to our front buffer
    swapChain->Present( 0, 0 );
}
