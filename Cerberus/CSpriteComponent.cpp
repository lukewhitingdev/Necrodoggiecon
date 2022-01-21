#include "CSpriteComponent.h"
#include "Engine.h"
#include "Utility/AssetManager/AssetManager.h"

void CSpriteComponent::SetRenderRect(XMUINT2 newSize)
{
	renderRect = newSize;

	if (material->loaded && texture->loaded)
	{
		material->material.Material.textureRect = renderRect;
		material->UpdateMaterial();	//Could be done once per update if a change has happened instead of here
	}
}

void CSpriteComponent::SetTextureOffset(XMFLOAT2 newOffset)
{
	textureOffset = newOffset;

	if (material->loaded && texture->loaded)
	{
		material->material.Material.textureOffset = textureOffset;
		material->UpdateMaterial();	//Could be done once per update if a change has happened instead of here
	}
}

void CSpriteComponent::SetTint(XMFLOAT4 newTint)
{
	tint = newTint;

	if (material->loaded)
	{
		material->material.Material.tint = tint;
		material->UpdateMaterial();	//Could be done once per update if a change has happened instead of here
	}
}

CSpriteComponent::CSpriteComponent()
{
	shouldUpdate = false;
	shouldDraw = true;

	mesh = AssetManager::GetDefaultMesh();
	material = new CMaterial();
	renderRect = XMUINT2(0, 0);
	spriteSize = XMUINT2(0, 0);
}

HRESULT CSpriteComponent::LoadTexture(std::string filePath)
{
	if (texture == nullptr)
		texture = AssetManager::GetTexture(filePath);
	else
		texture->LoadTextureDDS(filePath);

	if (texture == nullptr)
		return S_FALSE;

	renderRect = texture->textureSize;
	spriteSize = texture->textureSize;

	material->CreateMaterial(texture->textureSize);

	return S_OK;
}

void CSpriteComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void CSpriteComponent::Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer& cb, ID3D11Buffer* constantBuffer)
{
	if (!texture->loaded)	//change to texture valid check
	{
		Debug::LogError("Texture not loaded for CSpriteComponent.");
		return;
	}

	XMFLOAT4X4 compWorld = GetTransform();
	XMMATRIX mGO2 = XMLoadFloat4x4(&compWorld) * XMLoadFloat4x4(&parentMat);

	cb.mWorld = XMMatrixTranspose(mGO2);
	cb.vOutputColor = XMFLOAT4(1, 0, 1, 1);

	Engine::deviceContext->UpdateSubresource(constantBuffer, 0, nullptr, &cb, 0, 0);

	// Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	Engine::deviceContext->IASetVertexBuffers(0, 1, &mesh->vertexBuffer, &stride, &offset);

	// Set index buffer
	Engine::deviceContext->IASetIndexBuffer(mesh->indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// Set primitive topology
	Engine::deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Engine::deviceContext->PSSetConstantBuffers(1, 1, &material->materialConstantBuffer);

	context->PSSetShaderResources(0, 1, &texture->textureResourceView);
	context->PSSetSamplers(0, 1, &texture->samplerLinear);
	
	context->DrawIndexed(6, 0, 0);
}

CSpriteComponent::~CSpriteComponent()
{
	delete material;
}

XMFLOAT4X4 CSpriteComponent::GetTransform()
{
	if (updateTransform)
	{
		Vector3 scale = GetScale();
		Vector3 position = GetPosition();
		float rotation = GetRotation();

		XMMATRIX mat = XMMatrixScaling(scale.x * spriteSize.x, scale.y * spriteSize.y, scale.z)
			* XMMatrixRotationRollPitchYaw(0, 0, rotation)
			* XMMatrixTranslation(position.x, position.y, position.z);

		XMStoreFloat4x4(&world, mat);

		updateTransform = false;
	}

	return world;
}
