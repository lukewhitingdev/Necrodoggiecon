#include "CTexture.h"

CTexture::CTexture()
{

}

HRESULT CTexture::LoadTextureDDS(const wchar_t* filePath)
{
	// load and setup textures
	HRESULT hr = CreateDDSTextureFromFile(Engine::device, filePath, nullptr, &textureResourceView);
	if (FAILED(hr))
		return hr;

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = Engine::device->CreateSamplerState(&sampDesc, &samplerLinear);

	material.Material.UseTexture = true;

	// Create the material constant buffer
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(MaterialPropertiesConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = Engine::device->CreateBuffer(&bd, nullptr, &materialConstantBuffer);
	if (FAILED(hr))
		return hr;

	Engine::deviceContext->UpdateSubresource(materialConstantBuffer, 0, nullptr, &material, 0, 0);

	return hr;
}

CTexture::~CTexture()
{
	if (textureResourceView)
		textureResourceView->Release();
	textureResourceView = nullptr;

	if (samplerLinear)
		samplerLinear->Release();
	samplerLinear = nullptr;

	if (materialConstantBuffer)
		materialConstantBuffer->Release();
	materialConstantBuffer = nullptr;
}
