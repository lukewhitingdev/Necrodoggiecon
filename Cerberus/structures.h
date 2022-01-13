#pragma once

using namespace DirectX;

//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------


struct ConstantBuffer
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;
	XMFLOAT4 vOutputColor;
};

struct _Material
{
	_Material()
		: UseTexture(false)
		, textureSize(0,0)
		, textureRect(0,0)
	{}

	int		UseTexture;
	float	padding1[3];

	XMUINT2	textureSize;
	XMUINT2	textureRect;
};

struct MaterialPropertiesConstantBuffer
{
	_Material   Material;
};