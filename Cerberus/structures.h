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
	{}

	int                 UseTexture;
	// Add some padding to complete the 16 byte boundary.
	float               Padding[3];
	//----------------------------------- (16 byte boundary)
}; // Total:                                80 bytes (5 * 16)

struct MaterialPropertiesConstantBuffer
{
	_Material   Material;
};