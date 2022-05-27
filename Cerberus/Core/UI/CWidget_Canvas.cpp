/*******************************************************************
 * \file   CWidget_Canvas.cpp
 * \brief  The main class that controls widgets. All widgets should be instantiated within a widget object of this type.
 * 
 * \author Samuel Elliot Jackson
 * \date   May 2022
 *********************************************************************/
#include "CWidget_Canvas.h"
#include "Cerberus/Core/Utility/CameraManager/CameraManager.h"
#include "Cerberus/Core/Components/CTextRenderComponent.h"
#include "Cerberus/Core/UI/CWidget_Button.h"
#include "Cerberus/Core/UI/CWidget_Image.h"
#include "Cerberus/Core/UI/CWidget_Text.h"
#include "Cerberus/Core/Utility/Math/Math.h"


/**
 * Standard initialiser.
 * 
 */
CWidget_Canvas::CWidget_Canvas()
{
	SetShouldUpdate(true);
	InitialiseCanvas();
}


/**
 * Virtual function, Canvas is setup inside this function from within the child classes of this class.
 * 
 */
void CWidget_Canvas::InitialiseCanvas()
{
	
}

/**
 * Inherited from CEntity Update. calculates whether the mouse is interacting with any button.
 * 
 * \param deltaTime Time since previous frame
 */
void CWidget_Canvas::Update(float deltaTime)
{
	if (WidgetIsVisible)
	{
		for (int i = 0; i < buttonList.size(); i++)
		{
			buttonList[i]->IsButtonFocused(GetMousePosition());

			if (InputManager::IsMouseButtonPressed(InputManager::Mouse::LButton))
			{
				buttonList[i]->IsButtonFocused(GetMousePosition());

				if (InputManager::IsMouseButtonPressed(InputManager::Mouse::LButton))
				{
					buttonList[i]->ButtonPressed(true);
					mousePressed = true;
				}

				if (InputManager::IsMouseButtonReleased(InputManager::Mouse::LButton))
				{

					//buttonList[i]->ButtonPressed(false);
					mousePressed = false;
				}
			}
			else if (InputManager::IsMouseButtonReleased(InputManager::Mouse::LButton))
			{
				buttonList[i]->ButtonPressed(false);
			}
		}
	}
}
	
/**
 * Calculates the mouse position.
 * 
 * \return returns the position of the mouse.
 */
Vector2 CWidget_Canvas::GetMousePosition()
{

	Vector3 tempPos = Vector3(InputManager::mousePos.x - Engine::windowWidth * 0.5f, -InputManager::mousePos.y + Engine::windowHeight * 0.5f, GetPosition().z);
	return Vector2(tempPos.x, tempPos.y);
}


/**
 * Creates and initialises a button widget.
 * 
 * \param Position Position on screen. Anchor acts as origin.
 * \param Anchor Anchor of the widget in screen-space.
 * \param ButtonName Name of the button. Directly updates the text on button
 * \param ZOrder Z-Order
 * \return returns the created widget
 */
CWidget_Button* CWidget_Canvas::CreateButton(Vector2 Position, Vector2 Anchor, std::string& ButtonName, int ZOrder)
{
	CWidget_Button* Button = Engine::CreateEntity<CWidget_Button>();
	Button->SetText(ButtonName);

	Button->SetWidgetTransform(Position, Anchor, ZOrder);
	buttonList.push_back(Button);
	AddChild(Button);
	return Button;
}
/**
 * Creates and initialises an Image Widget.
 * 
 * \param Position Position on screen. Anchor acts as origin.
 * \param Anchor Anchor of the widget in screen-space.
 * \param ZOrder Z-Order
 * \return returns the created widget.
 */
CWidget_Image* CWidget_Canvas::CreateImage(Vector2 Position, Vector2 Anchor, int ZOrder)
{
	CWidget_Image* Image = Engine::CreateEntity<CWidget_Image>();
	Image->SetWidgetTransform(Position, Anchor, ZOrder);
	AddChild(Image);
	return Image;
}

/**
 * Creates and initialises a Text Widget.
 *
 * \param Position Position on screen. Anchor acts as origin.
 * \param Anchor Anchor of the widget in screen-space.
 * \param ZOrder Z-Order
 * \param Text The text to initialise the widget with.
 * \return returns the created widget.
 */
CWidget_Text* CWidget_Canvas::CreateText(Vector2 Position, Vector2 Anchor, int ZOrder, std::string& Text)
{
	CWidget_Text* Widget = Engine::CreateEntity<CWidget_Text>();
	Widget->SetWidgetTransform(Position, Anchor, ZOrder);
	Widget->GetText()->SetText(Text);
	AddChild(Widget);
	return Widget;
}

/**
 * Sets the visibility of the canvas and any widgets parented to it..
 * 
 * \param IsVisible Should the canvas be rendered.
 */
void CWidget_Canvas::SetVisibility(bool IsVisible)
{
	WidgetIsVisible = IsVisible;
	for (int i = 0; i < GetChildren().size(); i++)
	{
		GetChildren()[i]->SetVisibility(IsVisible);
	}


}
