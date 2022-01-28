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
	usedSpriteCount = unsigned short(newText.length());
	if (usedSpriteCount > sprites.size())	//Add a reserve so you don't constantly create and delete stuff.
	{
		int count = usedSpriteCount - int(sprites.size());
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
			int count = usedSpriteCount - int(sprites.size());
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
		sprites[i]->SetSpriteSize(XMUINT2(characterDrawSize.x, characterDrawSize.y));
		sprites[i]->SetTextureOffset(XMFLOAT2(float(characterSize.x) * float(newText[i] % spriteSheetColumns), float(characterSize.y) * float(floor(newText[i] / spriteSheetColumns))));

		switch (justification)
		{
		case TextJustification::Right:
			sprites[i]->SetPosition(Vector3(sprites[i]->GetSpriteSize().x * float(i), 0, 0));
			break;
		case TextJustification::Center:
			sprites[i]->SetPosition(Vector3(sprites[i]->GetSpriteSize().x * float(i) - ((float(sprites[i]->GetSpriteSize().x) * newText.length() * 0.5f) + sprites[i]->GetSpriteSize().x * -0.5f), 0, 0));
			break;
		case TextJustification::Left:
			sprites[i]->SetPosition(Vector3(sprites[i]->GetSpriteSize().x * float(i) - (sprites[i]->GetSpriteSize().x * newText.length() * 1.0f), 0, 0));
			break;
		}
	}
}

void CTextRenderComponent::SetReserveCount(unsigned short newReserveCount)
{
	reserveSpriteCount = newReserveCount;

	int count = reserveSpriteCount - int(sprites.size());
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

void CTextRenderComponent::SetJustification(TextJustification newJustification)
{
	justification = newJustification;
	SetText(text);
}

void CTextRenderComponent::SetCharacterSize(XMUINT2 newSize)
{
	characterSize = newSize;
	SetText(text);
}

void CTextRenderComponent::SetCharacterDrawSize(XMUINT2 newSize)
{
	characterDrawSize = newSize;
	SetText(text);
}

void CTextRenderComponent::SetSpriteSheetColumnsCount(unsigned short newColumnsCount)
{
	spriteSheetColumns = newColumnsCount;
	SetText(text);
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
