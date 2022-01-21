#include "CTextRenderComponent.h"
#include "CCamera.h"

CTextRenderComponent::CTextRenderComponent()
{
	shouldUpdate = false;
	shouldDraw = true;

	SetReserveCount(reserveSpriteCount);
}

HRESULT CTextRenderComponent::SetFont(std::string filePath)
{
	HRESULT hr = S_OK;
	for (auto& e : sprites)
	{
		hr = e->LoadTexture(filePath);
		if (FAILED(hr))
			return hr;
	}

	return hr;
}

void CTextRenderComponent::SetText(std::string newText)
{
	usedSpriteCount = newText.length();
	if (usedSpriteCount > sprites.size())	//Add a reserve so you don't constantly create and delete stuff.
	{
		int count = usedSpriteCount - sprites.size();
		for (int i = 0; i < count; i++)
		{
			sprites.push_back(new CSpriteComponent());
			CSpriteComponent* t = sprites.back();
			t->LoadTexture(font);
			Debug::Log("Add more sprites! size: %i", sprites.size());
		}
	}
	else
	{
		if (usedSpriteCount < sprites.size() && usedSpriteCount >= reserveSpriteCount)
		{
			int count = usedSpriteCount - sprites.size();
			for (int i = count; i < 0; i++)
			{
				CSpriteComponent* t = sprites.back();
				delete t;
				sprites.pop_back();
				Debug::Log("Remove some sprites! size: %i", sprites.size());
			}
		}
	}

	for (int i = 0; i < usedSpriteCount; i++)
	{
		sprites[i]->SetRenderRect(characterSize);
		sprites[i]->SetSpriteSize(XMUINT2(characterSize.x * 2, characterSize.y * 2));
		sprites[i]->SetTextureOffset(XMFLOAT2(characterSize.x * (newText[i] % spriteSheetWidth), characterSize.y * floor(newText[i] / spriteSheetWidth)));

		switch (justification)
		{
		case TextJustification::Right:
			sprites[i]->SetPosition(Vector3(sprites[i]->GetSpriteSize().x * i, 0, 0));
			break;
		case TextJustification::Center:
			sprites[i]->SetPosition(Vector3(sprites[i]->GetSpriteSize().x * i - ((sprites[i]->GetSpriteSize().x * newText.length() * .5) + sprites[i]->GetSpriteSize().x * -.5), 0, 0));
			break;
		case TextJustification::Left:
			//sprites[i]->SetPosition(Vector3(sprites[i]->GetSpriteSize().x * i - ((sprites[i]->GetSpriteSize().x * newText.length()) + sprites[i]->GetSpriteSize().x), 0, 0));
			break;
		}
	}
}

void CTextRenderComponent::SetReserveCount(unsigned short newReserveCount)
{
	reserveSpriteCount = newReserveCount;

	int count = reserveSpriteCount - sprites.size();
	for (int i = 0; i < count; i++)
	{
		sprites.push_back(new CSpriteComponent());
		CSpriteComponent* t = sprites.back();
		t->LoadTexture(font);
	}

	for (int i = count; i < 0; i++)
	{
		CSpriteComponent* t = sprites.back();
		delete t;
		sprites.pop_back();
	}

	if (reserveSpriteCount < usedSpriteCount)
		usedSpriteCount = reserveSpriteCount;

	Debug::Log("Resized TextRenderComp to %i sprites", sprites.size());
}

void CTextRenderComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void CTextRenderComponent::Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer)
{
	XMFLOAT4X4 compWorld = GetTransform();
	XMMATRIX mGO2 = XMLoadFloat4x4(&compWorld) * XMLoadFloat4x4(&parentMat);
	XMStoreFloat4x4(&compWorld, mGO2);

	if (ui)
	{
		cb.mView = XMMatrixIdentity();
		cb.mProjection = XMMatrixTranspose(Engine::projMatrixUI);
	}

	for (int i = 0; i < usedSpriteCount; i++)
		sprites[i]->Draw(context, compWorld, cb, constantBuffer);
}

CTextRenderComponent::~CTextRenderComponent()
{
	for (auto& e : sprites)
		delete e;

	sprites.clear();
}

XMFLOAT4X4 CTextRenderComponent::GetTransform()
{
	if (updateTransform)
	{
		if (!ui)
		{
			Vector3 scale = GetScale();
			Vector3 position = GetPosition();
			float rotation = GetRotation();

			XMMATRIX mat = XMMatrixScaling(scale.x, scale.y, scale.z)
				* XMMatrixRotationRollPitchYaw(0, 0, rotation)
				* XMMatrixTranslation(position.x, position.y, position.z);

			XMStoreFloat4x4(&world, mat);
		}
		else
		{
			Vector3 scale = GetScale();
			Vector3 position = GetPosition();
			float rotation = GetRotation();

			XMFLOAT2 anchorNorm = XMFLOAT2(anchor.x * 2 - 1, anchor.y * 2 - 1);
			/*XMFLOAT2 anchScaler = XMFLOAT2((1 - Engine::windowWidth / 1280.0f) * (anchorNorm.x * Engine::windowWidth * .5),
											(1 - Engine::windowHeight / 720.0f) * (anchorNorm.y * Engine::windowHeight * .5));*/

			XMFLOAT2 anchPoint = XMFLOAT2((anchorNorm.x * (Engine::windowWidth - 1280.0f) * .5),
				(anchorNorm.y * (Engine::windowHeight - 720.0f) * .5));

			XMFLOAT2 anchAdd = XMFLOAT2(position.x - anchPoint.x, position.y - anchPoint.y);

			XMMATRIX mat = XMMatrixScaling(scale.x, scale.y, scale.z)
				* XMMatrixRotationRollPitchYaw(0, 0, rotation)
				* XMMatrixTranslation(position.x + anchPoint.x, position.y + anchPoint.y, position.z);

			XMStoreFloat4x4(&world, mat);
		}

		//updateTransform = false;
	}

	return world;
}
