#include "Cerberus/Core/UI/CWidget_Text.h"
#include "Cerberus/Core/Components/CTextRenderComponent.h"

void CWidget_Text::SetWidgetTransform(Vector2 Position, Vector2 Anchor, int ZOrder)
{
	textRenderer->SetPosition(Position.x, Position.y, ZOrder - 1);
	textRenderer->SetScale(1, 1, 0);
	textRenderer->SetAnchor(XMFLOAT2(Anchor.x, Anchor.y));
}

void CWidget_Text::SetVisibility(bool IsVisible)
{

	
	textRenderer->shouldDraw = IsVisible;
	for (int i = 0; i < GetChildren().size(); i++)
	{
		GetChildren()[i]->SetVisibility(IsVisible);
	}
}
