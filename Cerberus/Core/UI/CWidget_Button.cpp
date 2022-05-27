/*****************************************************************//**
 * \file   CWidget_Button.cpp
 * \brief  
 * 
 * \author Samuel Elliot Jackson
 * \date   May 2022
 *********************************************************************/

#include "Cerberus/Core/UI/CWidget_Button.h"
#include "Cerberus/Core/Components/CSpriteComponent.h"
#include "Cerberus/Core/Components/CTextRenderComponent.h"
#include "Cerberus/Core/UI/CWidget_Canvas.h"

using namespace std;

/**
 * Standard constructor.
 * 
 */
CWidget_Button::CWidget_Button()
{
	sprite = AddComponent<CSpriteComponent>(NAME_OF(sprite));
	sprite->SetIsUI(true);


	textRenderer = AddComponent<CTextRenderComponent>(NAME_OF(textRenderer));
	textRenderer->SetIsUI(true);
	
	
	ButtonPressedBind = nullptr;
	ButtonReleasedBind = nullptr;
	HoverEndBind = nullptr;
	HoverStartBind = nullptr;
	textRenderer->SetFont("Resources/Engine/fontBlack.png");
}

/**
 * Sets the button Text.
 * 
 * \param TextBody The text to set the button's text to.
 */
void CWidget_Button::SetText(std::string TextBody)
{
	textRenderer->SetText(TextBody);


}

/**
 * Sets the button's visual size, does not effect the text.
 * 
 * \param Size
 */
void CWidget_Button::SetButtonSize(Vector2 Size)
{
	sprite->SetSpriteSize(DirectX::XMUINT2(Size.x, Size.y));
	sprite->SetRenderRect(DirectX::XMUINT2(64, 32));
	sprite->SetTextureOffset(DirectX::XMFLOAT2(0,0));
	spriteSize = Vector2(64, 32);

	
	
}

/**
 * Sets the texture of the button.
 * 
 * \param filePath
 */
void CWidget_Button::SetTexture(std::string filePath)
{
	sprite->LoadTexture(filePath);
}

/**
 * Sets the widget transform. This function is the primary method to move the Widget around on the screen.
 * 
 * \param Position Position of the widget on screen. Centered on the Anchor point.
 * \param Anchor Anchor point on the screen. 
 * \param ZOrder Render layer.
 */
void CWidget_Button::SetWidgetTransform(Vector2 Position, Vector2 Anchor, int ZOrder)
{
	sprite->SetPosition(Position.x, Position.y, ZOrder);
	sprite->SetScale(1, 1, 1);
	sprite->SetAnchor(XMFLOAT2(Anchor.x, Anchor.y));

	textRenderer->SetPosition(Position.x, Position.y, ZOrder - 1);
	textRenderer->SetScale(1, 1, 0);
	textRenderer->SetAnchor(XMFLOAT2(Anchor.x, Anchor.y));
}

/**
 * Standard entity update function.
 * 
 * \param deltaTime
 */
void CWidget_Button::Update(float deltaTime)
{
}

/**
 * Called when the button is pressed. Sets the texture offset to animate the button and calls the bound function if any.
 * 
 */
void CWidget_Button::OnButtonPressed()
{
	sprite->SetTextureOffset(DirectX::XMFLOAT2(0, (float)spriteSize.y * 1));
	if (ButtonPressedBind != nullptr) 	ButtonPressedBind();
	ButtonHeld = true;
}

/**
 * Called when the button is released. Sets the texture offset to animate the button and calls the bound function if any.
 *
 */
void CWidget_Button::OnButtonReleased()
{
	if (ButtonHeld)
	{
		sprite->SetTextureOffset(DirectX::XMFLOAT2((float)0, (float)spriteSize.y * 2));
		if (ButtonReleasedBind != nullptr) ButtonReleasedBind();
		ButtonHeld = false;
	}

}

/**
 * Called when the button is hovered. Sets the texture offset to animate the button and calls the bound function if any.
 *
 */
void CWidget_Button::OnButtonHoverStart()
{
	sprite->SetTextureOffset(DirectX::XMFLOAT2((float)0, (float)spriteSize.y * 2));
	if (HoverStartBind != nullptr) HoverStartBind();
	
}

/**
 * Called when the button is no longer hovered. Sets the texture offset to animate the button and calls the bound function if any.
 *
 */
void CWidget_Button::OnButtonHoverEnd()
{
	sprite->SetTextureOffset(DirectX::XMFLOAT2(0, 0));
	if (HoverEndBind != nullptr) 	HoverEndBind();
}


/**
 * Sets the visibility of the button and any widgets parented to this widget.
 * 
 * \param IsVisible Whether the is visible or not.
 */
void CWidget_Button::SetVisibility(bool IsVisible)
{
	sprite->SetShouldDraw(IsVisible);
	textRenderer->SetShouldDraw(IsVisible);
	WidgetIsVisible = IsVisible;
	for (int i = 0; i < GetChildren().size(); i++)
	{
		GetChildren()[i]->SetVisibility(IsVisible);
	}
}

/**
 * Determines if the Widget currently has focus of the mouse(is the mouse within button bounds).
 * 
 * \param mPos
 */
void CWidget_Button::IsButtonFocused(Vector2 mPos)
{

	Vector2 Scale = Vector2(sprite->GetSpriteSize().x, sprite->GetSpriteSize().y);
	Vector2 Pos = Vector2(sprite->GetPosition().x, sprite->GetPosition().y);
	Pos -= Scale / 2;
	if (!hasFocus)
	{
		if (mPos.x > Pos.x && mPos.x < Scale.x + Pos.x &&
			mPos.y > Pos.y && mPos.y < Scale.y + Pos.y)
		{
			
			if (!hasFocus)
			{
				OnButtonHoverStart();
			}
			
			hasFocus = true;
			
			
			

		}

	}
	else
	{
		if (!(mPos.x > Pos.x && mPos.x < Scale.x + Pos.x &&
			mPos.y > Pos.y && mPos.y < Scale.y + Pos.y))
		{

			if (hasFocus)
			{
				OnButtonHoverEnd();
			}
			hasFocus = false;

			

		}
		

	}
}

/**
 * Triggered when the button is clicked. Triggers pressed and released functions.
 * 
 * \param buttonPressed
 */
void CWidget_Button::ButtonPressed(bool buttonPressed)
{

	if (hasFocus)
	{

		if (buttonPressed) OnButtonPressed();
		else OnButtonReleased();
	}
	
}
