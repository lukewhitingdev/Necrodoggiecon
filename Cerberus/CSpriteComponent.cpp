#include "CSpriteComponent.h"
#include "Engine.h"

CSpriteComponent::CSpriteComponent()
{
	shouldUpdate = false;
	shouldDraw = true;

	mesh = new CMesh();
	texture = new CTexture();
}

HRESULT CSpriteComponent::LoadTexture(const wchar_t* filePath)
{
	HRESULT hr = texture->LoadTextureDDS(filePath);
	if(hr == S_OK)
		textureLoaded = true;

	return hr;
}

void CSpriteComponent::Update(float deltaTime)
{

}

void CSpriteComponent::Draw(ID3D11DeviceContext* context)
{
	if (!textureLoaded)
	{
		Debug::LogError("Texture not loaded for CSpriteComponent.");
		return;
	}

	// Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	Engine::deviceContext->IASetVertexBuffers(0, 1, &mesh->vertexBuffer, &stride, &offset);

	// Set index buffer
	Engine::deviceContext->IASetIndexBuffer(mesh->indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// Set primitive topology
	Engine::deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Engine::deviceContext->PSSetConstantBuffers(1, 1, &texture->materialConstantBuffer);

	context->PSSetShaderResources(0, 1, &texture->textureResourceView);
	context->PSSetSamplers(0, 1, &texture->samplerLinear);
	
	context->DrawIndexed(6, 0, 0);
}

CSpriteComponent::~CSpriteComponent()
{
	delete mesh;
	delete texture;
}
