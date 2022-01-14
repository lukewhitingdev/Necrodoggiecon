#pragma once
#include "Engine.h"

struct _Material
{
	_Material()
		: UseTexture(false)
		, textureSize(0, 0)
		, textureRect(0, 0)
		, textureOffset(0, 0)
	{}

	int		UseTexture;
	float	padding1[3];

	XMUINT2	textureSize;
	XMUINT2	textureRect;

	XMFLOAT2 textureOffset;
	float padding2[2];
};

struct MaterialPropertiesConstantBuffer
{
	_Material   Material;
};

struct CMaterial
{
	MaterialPropertiesConstantBuffer material;
	ID3D11Buffer* materialConstantBuffer = nullptr;

	bool loaded = false;

	CMaterial();
	HRESULT CreateMaterial(XMUINT2 texSize);
	void UpdateMaterial();
	~CMaterial();
};

