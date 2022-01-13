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

	CMesh();
	HRESULT LoadMesh();
	~CMesh();
};

