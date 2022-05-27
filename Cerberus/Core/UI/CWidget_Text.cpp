/*****************************************************************//**
 * \file   CWidget_Text.cpp
 * \brief  
 * 
 * \author Samuel Elliot Jackson
 * \date   May 2022
 *********************************************************************/
#include "Cerberus/Core/UI/CWidget_Text.h"
#include "Cerberus/Core/Components/CTextRenderComponent.h"

/**
 * Standard constructor.
 * 
 */
CWidget_Text::CWidget_Text()
{
	textRenderer = AddComponent<CTextRenderComponent>(NAME_OF(textRenderer));
	//textRenderer->SetIsUI(true);
	textRenderer->SetFont("Resources/Engine/fontBlack.png");
}
/**
 * Inherited CEntity update function.
 *
 * \param deltaTime Time between previous frame.
 */
void CWidget_Text::Update(float deltaTime)
{
}

/**
 * Sets the widget transform. This function is the primary method to move the Widget around on the screen.
 *
 * \param Position Position of the widget on screen. Centered on the Anchor point.
 * \param Anchor Anchor point on the screen.
 * \param ZOrder Render layer.
 */
void CWidget_Text::SetWidgetTransform(Vector2 Position, Vector2 Anchor, int ZOrder)
{
	textRenderer->SetPosition(Position.x, Position.y, ZOrder);
	textRenderer->SetScale(1, 1, 0);
	textRenderer->SetAnchor(XMFLOAT2(Anchor.x, Anchor.y));
}

/**
 * Sets the visibility of the button and any widgets parented to this widget.
 *
 * \param IsVisible Whether the is visible or not.
 */
void CWidget_Text::SetVisibility(bool IsVisible)
{

	WidgetIsVisible = IsVisible;
	textRenderer->SetShouldDraw(IsVisible);
	for (int i = 0; i < GetChildren().size(); i++)
	{
		GetChildren()[i]->SetVisibility(IsVisible);
	}
}
