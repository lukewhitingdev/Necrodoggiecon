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

	ID3D11Resource* resource;
	textureResourceView->GetResource(&resource);
	ID3D11Texture2D* tex2D = static_cast<ID3D11Texture2D*>(resource);
	D3D11_TEXTURE2D_DESC texDsc;
	tex2D->GetDesc(&texDsc);
	textureSize.x = texDsc.Width;
	textureSize.y = texDsc.Height;

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = Engine::device->CreateSamplerState(&sampDesc, &samplerLinear);

	material.Material.UseTexture = true;
	material.Material.textureSize = textureSize;
	material.Material.textureRect = textureSize;

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
