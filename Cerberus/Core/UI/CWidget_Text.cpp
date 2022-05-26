#include "Cerberus/Core/UI/CWidget_Text.h"
#include "Cerberus/Core/Components/CTextRenderComponent.h"

CWidget_Text::CWidget_Text()
{
	textRenderer = AddComponent<CTextRenderComponent>(NAME_OF(textRenderer));
	textRenderer->SetIsUI(true);
	textRenderer->SetFont("Resources/Engine/fontBlack.png");
}

void CWidget_Text::Update(float deltaTime)
{
}

void CWidget_Text::SetWidgetTransform(Vector2 Position, Vector2 Anchor, int ZOrder)
{
	textRenderer->SetPosition(Position.x, Position.y, ZOrder);
	textRenderer->SetScale(1, 1, 0);
	textRenderer->SetAnchor(XMFLOAT2(Anchor.x, Anchor.y));
}

void CWidget_Text::SetVisibility(bool IsVisible)
{

	WidgetIsVisible = IsVisible;
	textRenderer->SetShouldDraw(IsVisible);
	for (int i = 0; i < GetChildren().size(); i++)
	{
		GetChildren()[i]->SetVisibility(IsVisible);
	}
}
