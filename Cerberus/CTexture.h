#pragma once
#include "Engine.h"

struct CTexture
{
	ID3D11ShaderResourceView* textureResourceView;
	ID3D11SamplerState* samplerLinear;
	MaterialPropertiesConstantBuffer material;
	ID3D11Buffer* materialConstantBuffer = nullptr;

	CTexture();
	HRESULT LoadTextureDDS(const wchar_t* filePath);
	~CTexture();
};