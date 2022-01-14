#pragma once
#include "Engine.h"

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

