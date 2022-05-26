#include "CWidget_Canvas.h"
#include "Cerberus/Core/Utility/CameraManager/CameraManager.h"
#include "Cerberus/Core/Components/CTextRenderComponent.h"
#include "Cerberus/Core/UI/CWidget_Button.h"
#include "Cerberus/Core/UI/CWidget_Image.h"
#include "Cerberus/Core/UI/CWidget_Text.h"
#include "Cerberus/Core/Utility/Math/Math.h"


CWidget_Canvas::CWidget_Canvas()
{
	SetShouldUpdate(true);
	InitialiseCanvas();
}



void CWidget_Canvas::InitialiseCanvas()
{
	
}

void CWidget_Canvas::Update(float deltaTime)
{
	if (buttonList.size() > 20)
	{
		int Temp = buttonList.size();
	}
	if (WidgetIsVisible)
	{
		for (int i = 0; i < buttonList.size(); i++)
		{
			if (buttonList[i] != nullptr)
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
}
	

Vector2 CWidget_Canvas::GetMousePosition()
{

	Vector3 tempPos = Vector3(InputManager::mousePos.x - Engine::windowWidth * 0.5f, -InputManager::mousePos.y + Engine::windowHeight * 0.5f, GetPosition().z);
	return Vector2(tempPos.x, tempPos.y);
}



CWidget_Button* CWidget_Canvas::CreateButton(Vector2 Position, Vector2 Anchor, std::string& ButtonName, int ZOrder)
{
	CWidget_Button* Button = Engine::CreateEntity<CWidget_Button>();
	Button->SetText(ButtonName);

	Button->SetWidgetTransform(Position, Anchor, ZOrder);
	buttonList.push_back(Button);
	AddChild(Button);
	return Button;
}

CWidget_Image* CWidget_Canvas::CreateImage(Vector2 Position, Vector2 Anchor, int ZOrder)
{
	CWidget_Image* Image = Engine::CreateEntity<CWidget_Image>();
	Image->SetWidgetTransform(Position, Anchor, ZOrder);
	AddChild(Image);
	return Image;
}

CWidget_Text* CWidget_Canvas::CreateText(Vector2 Position, Vector2 Anchor, int ZOrder, std::string& Text)
{
	CWidget_Text* Widget = Engine::CreateEntity<CWidget_Text>();
	Widget->SetWidgetTransform(Position, Anchor, ZOrder);
	Widget->GetText()->SetText(Text);
	AddChild(Widget);
	return Widget;
}

void CWidget_Canvas::SetVisibility(bool IsVisible)
{
	WidgetIsVisible = IsVisible;
	for (int i = 0; i < GetChildren().size(); i++)
	{
		GetChildren()[i]->SetVisibility(IsVisible);
	}


}
