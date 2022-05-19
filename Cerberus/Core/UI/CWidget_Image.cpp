#include "CWidget_Image.h"
#include "Cerberus/Core/Components/CSpriteComponent.h"


CWidget_Image::CWidget_Image()
{
	sprite = AddComponent<CSpriteComponent>();
}

void CWidget_Image::SetWidgetTransform(Vector2 Position, Vector2 Anchor, int ZOrder)
{
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
	for (int i = 0; i < GetChildren().size(); i++)
	{
		GetChildren()[i]->SetVisibility(IsVisible);
	}
}
