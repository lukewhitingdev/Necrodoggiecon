#include "CTextRenderComponent.h"

CTextRenderComponent::CTextRenderComponent()
{
	shouldUpdate = false;
	shouldDraw = true;
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
	int count = newText.length() - sprites.size();
	for (int i = 0; i < count; i++)
	{
		sprites.push_back(new CSpriteComponent());
		CSpriteComponent* t = sprites.back();
		t->LoadTexture(font);
		t->SetRenderRect(characterSize);
		t->SetSpriteSize(XMUINT2(characterSize.x * 2, characterSize.y * 2));
	}

	for (int i = 0; i > count; i--)
	{
		CSpriteComponent* t = sprites.back();
		delete t;
		sprites.pop_back();
	}

	for (int i = 0; i < sprites.size(); i++)
	{
		//set the text coords here
		sprites[i]->SetTextureOffset(XMFLOAT2(characterSize.x * (newText[i] % 16), characterSize.y * floor(newText[i] / 16)));
		sprites[i]->SetPosition(Vector3(sprites[i]->GetSpriteSize().x * i - ((sprites[i]->GetSpriteSize().x * newText.length() * .5) + sprites[i]->GetSpriteSize().x * -.5), 0, 0));
	}
}

void CTextRenderComponent::Update(float deltaTime)
{

}

void CTextRenderComponent::Draw(ID3D11DeviceContext* context, XMFLOAT4X4 parentMat, ConstantBuffer& cb, ID3D11Buffer* constantBuffer)
{
	XMFLOAT4X4 compWorld = GetTransform();
	XMMATRIX mGO2 = XMLoadFloat4x4(&compWorld) * XMLoadFloat4x4(&parentMat);
	XMStoreFloat4x4(&compWorld, mGO2);

	for (auto& e : sprites)
		e->Draw(context, compWorld, cb, constantBuffer);
}

CTextRenderComponent::~CTextRenderComponent()
{
	for (auto& e : sprites)
		delete e;

	sprites.clear();
}
