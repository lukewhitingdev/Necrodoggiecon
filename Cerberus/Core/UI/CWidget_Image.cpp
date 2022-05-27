/*****************************************************************//**
 * \file   CWidget_Image.cpp
 * \brief  A widget class that contains an image.
 * 
 * \author Samuel Elliot Jackson
 * \date   May 2022
 *********************************************************************/
#include "CWidget_Image.h"
#include "Cerberus/Core/Components/CTextRenderComponent.h"
#include "Cerberus/Core/Components/CSpriteComponent.h"


/**
 * Standard Constructor.
 * 
 */
CWidget_Image::CWidget_Image()
{
	sprite = AddComponent<CSpriteComponent>(NAME_OF(sprite));
	//sprite->SetIsUI(true);

	textRenderer = AddComponent<CTextRenderComponent>(NAME_OF(textRenderer));
  textRenderer->SetFont("Resources/Engine/fontBlack.png");
	//textRenderer->SetIsUI(true);
}

/**
 * Inherited CEntity update function.
 * 
 * \param deltaTime Time between previous frame.
 */
void CWidget_Image::Update(float deltaTime)
{
}

/**
 * Sets the widget transform. This function is the primary method to move the Widget around on the screen.
 *
 * \param Position Position of the widget on screen. Centered on the Anchor point.
 * \param Anchor Anchor point on the screen.
 * \param ZOrder Render layer.
 */
void CWidget_Image::SetWidgetTransform(Vector2 Position, Vector2 Anchor, int ZOrder)
{
	sprite->SetPosition(Position.x, Position.y, ZOrder);
	sprite->SetScale(1, 1, 0);
	sprite->SetAnchor(XMFLOAT2(Anchor.x, Anchor.y));

	textRenderer->SetPosition(Position.x, Position.y, ZOrder - 1);
	textRenderer->SetScale(1, 1, 0);
	textRenderer->SetAnchor(XMFLOAT2(Anchor.x, Anchor.y));
}

/**
 * Initialises the sprite data from filepath, sets the size.
 * 
 * \param SpriteSize
 * \param filePath
 */
void CWidget_Image::SetSpriteData(Vector2 SpriteSize, std::string filePath)
{
	sprite->LoadTexture(filePath);

	sprite->SetSpriteSize(DirectX::XMUINT2(SpriteSize.x, SpriteSize.y));
	sprite->SetRenderRect(DirectX::XMUINT2(SpriteSize.x, SpriteSize.y));
	sprite->SetTextureOffset(DirectX::XMFLOAT2(0, 0));
}

/**
 * Sets the visibility of the button and any widgets parented to this widget.
 *
 * \param IsVisible Whether the is visible or not.
 */
void CWidget_Image::SetVisibility(bool IsVisible)
{
	sprite->SetShouldDraw(IsVisible);
	textRenderer->SetShouldDraw(IsVisible);
	WidgetIsVisible = IsVisible;
	for (int i = 0; i < GetChildren().size(); i++)
	{
		GetChildren()[i]->SetVisibility(IsVisible);
	}
}
