#pragma once
#include "Engine.h"

struct SimpleVertex
{
	XMFLOAT3 Pos;
	XMFLOAT2 TexCoord;
};

struct CMesh
{
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11ShaderResourceView* textureResourceView;
	ID3D11SamplerState* samplerLinear;
	MaterialPropertiesConstantBuffer material;
	ID3D11Buffer* materialConstantBuffer = nullptr;

	CMesh();
	HRESULT LoadMesh();
	~CMesh();
};

