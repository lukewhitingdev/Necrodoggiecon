/*****************************************************************//**
 * \file   CMesh.h
 * \brief  Holds all information about a mesh for use by CSpriteComponent.
 * 
 * \author Arrien Bidmead
 * \date   January 2022
 *********************************************************************/

#pragma once
#include "Engine.h"

struct SimpleVertex
{
	XMFLOAT3 Pos;
	XMFLOAT2 TexCoord;
};

/**
 * Holds all information about a mesh for use by CSpriteComponent.
 * Right now only stores a hardcoded quad - might need extending in future for new shapes.
 */
struct CMesh
{
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	bool loaded = false;

	CMesh();
	HRESULT LoadMesh();
	~CMesh();
};

