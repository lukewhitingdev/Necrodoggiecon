#include "CWidget_Image.h"
#include "Cerberus/Core/Components/CTextRenderComponent.h"
#include "Cerberus/Core/Components/CSpriteComponent.h"


CWidget_Image::CWidget_Image()
{
	sprite = AddComponent<CSpriteComponent>();
	sprite->ui = true;
	textRenderer = AddComponent<CTextRenderComponent>();
	textRenderer->ui = true;
}

void CWidget_Image::Update(float deltaTime)
{
}

void CWidget_Image::SetWidgetTransform(Vector2 Position, Vector2 Anchor, int ZOrder)
{
	sprite->SetPosition(Position.x, Position.y, ZOrder);
	sprite->SetScale(1, 1, 0);
	sprite->SetAnchor(XMFLOAT2(Anchor.x, Anchor.y));

	textRenderer->SetPosition(Position.x, Position.y, ZOrder - 1);
	textRenderer->SetScale(1, 1, 0);
	textRenderer->SetAnchor(XMFLOAT2(Anchor.x, Anchor.y));
}

void CWidget_Image::SetSpriteData(Vector2 SpriteSize, std::string filePath)
{
	sprite->LoadTexture(filePath);

	sprite->SetSpriteSize(DirectX::XMUINT2(SpriteSize.x, SpriteSize.y));
	sprite->SetRenderRect(DirectX::XMUINT2(SpriteSize.x, SpriteSize.y));
	sprite->SetTextureOffset(DirectX::XMFLOAT2(0, 0));
}

void CWidget_Image::SetVisibility(bool IsVisible)
{
	sprite->shouldDraw = IsVisible;
	textRenderer->shouldDraw = IsVisible;
	for (int i = 0; i < GetChildren().size(); i++)
	{
		GetChildren()[i]->SetVisibility(IsVisible);
	}
}
