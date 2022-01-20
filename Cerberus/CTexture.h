#pragma once
#include "Engine.h"

//Holds all information about a texture for use by CSpriteComponent
//Use load function to populate
struct CTexture
{
	XMUINT2 textureSize = {0,0};

	ID3D11ShaderResourceView* textureResourceView;
	ID3D11SamplerState* samplerLinear;
	bool loaded = false;

	CTexture();
	HRESULT LoadTextureDDS(std::string filePath);
	~CTexture();
};