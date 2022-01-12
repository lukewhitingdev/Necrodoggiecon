#include "CMesh.h"

CMesh::CMesh()
{
	LoadMesh();
}

HRESULT CMesh::LoadMesh()
{
	// Create vertex buffer
	SimpleVertex vertices[] =
	{
		{ XMFLOAT3(-1.0f, -1.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
	};

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData = {};
	InitData.pSysMem = vertices;
	HRESULT hr = Engine::device->CreateBuffer(&bd, &InitData, &vertexBuffer);
	if (FAILED(hr))
		return hr;

	// Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	Engine::deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	// Create index buffer
	WORD indices[] =
	{
		2,1,0,
		0,3,2,
	};

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 6;        // 36 vertices needed for 12 triangles in a triangle list
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = indices;
	hr = Engine::device->CreateBuffer(&bd, &InitData, &indexBuffer);
	if (FAILED(hr))
		return hr;

	// Set index buffer
	Engine::deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// Set primitive topology
	Engine::deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// load and setup textures
	hr = CreateDDSTextureFromFile(Engine::device, L"Resources\\stone.dds", nullptr, &textureResourceView);
	if (FAILED(hr))
		return hr;

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = Engine::device->CreateSamplerState(&sampDesc, &samplerLinear);

	material.Material.UseTexture = true;

	// Create the material constant buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(MaterialPropertiesConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = Engine::device->CreateBuffer(&bd, nullptr, &materialConstantBuffer);
	if (FAILED(hr))
		return hr;

	Engine::deviceContext->UpdateSubresource(materialConstantBuffer, 0, nullptr, &material, 0, 0);

    return hr;
}

CMesh::~CMesh()
{
	if (vertexBuffer)
		vertexBuffer->Release();
	vertexBuffer = nullptr;

	if (indexBuffer)
		indexBuffer->Release();
	indexBuffer = nullptr;

	if (textureResourceView)
		textureResourceView->Release();
	textureResourceView = nullptr;

	if (samplerLinear)
		samplerLinear->Release();
	samplerLinear = nullptr;

	if (materialConstantBuffer)
		materialConstantBuffer->Release();
	materialConstantBuffer = nullptr;
}
