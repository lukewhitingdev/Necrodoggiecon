#include "CTexture.h"

CTexture::CTexture()
{

}


HRESULT CTexture::LoadTextureDDS(std::string filePath)
{
	if (loaded)
	{
		if (textureResourceView)
			textureResourceView->Release();
		textureResourceView = nullptr;

		if (samplerLinear)
			samplerLinear->Release();
		samplerLinear = nullptr;

		loaded = false;
	}

	// Copied from -- https://docs.microsoft.com/en-us/cpp/text/how-to-convert-between-various-string-types?view=msvc-170
	// Convert char* string to a wchar_t* string.
	size_t newsize = strlen(filePath.c_str()) + 1;
	wchar_t* convertedString = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, convertedString, newsize, filePath.c_str(), _TRUNCATE);

	// load and setup textures
	HRESULT hr = CreateDDSTextureFromFile(Engine::device, convertedString, nullptr, &textureResourceView);
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

	loaded = true;
	return hr;
}


HRESULT CTexture::LoadTextureWIC(std::string filename)
{
	if (loaded)
	{
		if (textureResourceView)
			textureResourceView->Release();
		textureResourceView = nullptr;

		if (samplerLinear)
			samplerLinear->Release();
		samplerLinear = nullptr;

		loaded = false;
	}

	// Copied from -- https://docs.microsoft.com/en-us/cpp/text/how-to-convert-between-various-string-types?view=msvc-170
	// Convert char* string to a wchar_t* string.
	size_t newsize = strlen(filename.c_str()) + 1;
	wchar_t* convertedString = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, convertedString, newsize, filename.c_str(), _TRUNCATE);


	HRESULT hr = CreateWICTextureFromFile(Engine::device, convertedString, nullptr, &textureResourceView);
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

	loaded = true;
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
}
