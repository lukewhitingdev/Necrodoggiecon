#pragma once
#include "Engine.h"

class CMesh
{
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11ShaderResourceView* textureResourceView;
	ID3D11SamplerState* samplerLinear;
	MaterialPropertiesConstantBuffer material;
	ID3D11Buffer* materialConstantBuffer = nullptr;
public:
	CMesh();
	HRESULT LoadMesh();
	~CMesh();
};

