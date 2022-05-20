#include "Cerberus\Core\Components\CSpriteComponent.h"
#include "Cerberus\Core\Engine.h"
#include "Cerberus/Core/Utility/AssetManager/AssetManager.h"
#include "Cerberus\Core\Structs\CCamera.h"
#include "CSpriteComponent.h"

void CSpriteComponent::SetRenderRect(const XMUINT2& newSize)
{
	renderRect = newSize;

	if (material->loaded && texture->loaded)
	{
		material->material.Material.textureRect = renderRect;
		material->UpdateMaterial();	//Could be done once per update if a change has happened instead of here
	}
}

void CSpriteComponent::SetTextureOffset(const XMFLOAT2& newOffset)
{
	textureOffset = newOffset;

	if (material->loaded && texture->loaded)
	{
		material->material.Material.textureOffset = textureOffset;
		material->UpdateMaterial();	//Could be done once per update if a change has happened instead of here
	}
}

void CSpriteComponent::SetTint(const XMFLOAT4& newTint)
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
	SetShouldUpdate(false);
	SetShouldDraw(true);

	mesh = AssetManager::GetDefaultMesh();
	material = new CMaterial();
	renderRect = XMUINT2(0, 0);
	spriteSize = XMUINT2(0, 0);
}

HRESULT CSpriteComponent::LoadTexture(const std::string& filePath)
{
	texture = AssetManager::GetTexture(filePath);

	if (texture == nullptr)
		return E_FAIL;

	renderRect = texture->textureSize;
	spriteSize = texture->textureSize;

	material->CreateMaterial(texture->textureSize);

	return S_OK;
}

HRESULT CSpriteComponent::LoadTextureWIC(const std::string& filePath)
{
	texture = AssetManager::GetTextureWIC(filePath);

	if (texture == nullptr)
		return E_FAIL;

	renderRect = texture->textureSize;
	spriteSize = texture->textureSize;

	material->CreateMaterial(texture->textureSize);

	return S_OK;
}

void CSpriteComponent::SetUseTranslucency(const bool& newTranslucency)
{
	CComponent::SetUseTranslucency(newTranslucency);

	if (material->loaded && texture->loaded)
	{
		material->material.Material.translucent = true;
		material->UpdateMaterial();	//Could be done once per update if a change has happened instead of here
	}
}

void CSpriteComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void CSpriteComponent::Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer)
{
	if (texture == nullptr || !texture->loaded)	//change to texture valid check
	{
		Debug::LogError("Texture not loaded for CSpriteComponent.");
		return;
	}

	XMFLOAT4X4 compWorld = GetTransform();
	XMMATRIX mGO2 = XMLoadFloat4x4(&compWorld) * XMLoadFloat4x4(&parentMat);

	cb.mWorld = XMMatrixTranspose(mGO2);
	cb.vOutputColor = XMFLOAT4(1, 0, 1, 1);

	if (GetIsUI())
	{
		cb.mView = XMMatrixIdentity();
		cb.mProjection = XMMatrixTranspose(Engine::projMatrixUI);
	}

	Engine::deviceContext->UpdateSubresource(constantBuffer, 0, nullptr, &cb, 0, 0);

	// Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	Engine::deviceContext->IASetVertexBuffers(0, 1, &mesh->vertexBuffer, &stride, &offset);

	// Set index buffer
	Engine::deviceContext->IASetIndexBuffer(mesh->indexBuffer, DXGI_FORMAT_R16_UINT, 0);

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
	if (!GetIsUI())
	{
		if (updateTransform)
		{
			XMMATRIX mat = XMMatrixScaling(GetScale().x * spriteSize.x, GetScale().y * spriteSize.y, GetScale().z)
				* XMMatrixRotationRollPitchYaw(0, 0, GetRotation())
				* XMMatrixTranslation(GetPosition().x, GetPosition().y, GetPosition().z);

			XMStoreFloat4x4(&world, mat);

			updateTransform = false;
		}

		return world;
	}

	if (updateTransform && GetIsUI() || GetLastResolution().x != Engine::windowWidth || GetLastResolution().y != Engine::windowHeight)
	{
		SetLastResolution(XMUINT2(Engine::windowWidth, Engine::windowHeight));

		XMFLOAT2 anchorNorm = XMFLOAT2(GetAnchor().x * 2 - 1, GetAnchor().y * -2 + 1);

		XMFLOAT2 anchPoint = XMFLOAT2((anchorNorm.x * (float(Engine::windowWidth) - 1280.0f) * 0.5f),
			(anchorNorm.y * (float(Engine::windowHeight) - 720.0f) * 0.5f));

		XMFLOAT2 anchAdd = XMFLOAT2(GetPosition().x - anchPoint.x, GetPosition().y - anchPoint.y);

		XMMATRIX mat = XMMatrixScaling(GetScale().x * spriteSize.x, GetScale().y * spriteSize.y, GetScale().z)
			* XMMatrixRotationRollPitchYaw(0, 0, GetRotation())
			* XMMatrixTranslation(GetPosition().x + anchPoint.x, GetPosition().y + anchPoint.y, GetPosition().z);

		XMStoreFloat4x4(&world, mat);

		updateTransform = false;
	}

	return world;
}
