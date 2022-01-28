#include "CMaterial.h"

CMaterial::CMaterial()
{

}

HRESULT CMaterial::CreateMaterial(XMUINT2 texSize)
{
	if (loaded)
	{
		if (materialConstantBuffer)
			materialConstantBuffer->Release();
		materialConstantBuffer = nullptr;
	}

	material.Material.UseTexture = true;
	material.Material.textureSize = texSize;
	material.Material.textureRect = texSize;
	material.Material.textureOffset = XMFLOAT2(0,0);
	material.Material.tint = XMFLOAT4(0,0,0,0);

	// Create the material constant buffer
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(MaterialPropertiesConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	HRESULT hr = Engine::device->CreateBuffer(&bd, nullptr, &materialConstantBuffer);
	if (FAILED(hr))
		return hr;

	UpdateMaterial();

	loaded = true;
	return hr;
}

void CMaterial::UpdateMaterial()
{
	Engine::deviceContext->UpdateSubresource(materialConstantBuffer, 0, nullptr, &material, 0, 0);
}

CMaterial::~CMaterial()
{
	if (materialConstantBuffer)
		materialConstantBuffer->Release();
	materialConstantBuffer = nullptr;
}
