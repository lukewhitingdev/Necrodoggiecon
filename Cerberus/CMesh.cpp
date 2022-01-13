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
		{ XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(-0.5f, 0.5f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
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
}
