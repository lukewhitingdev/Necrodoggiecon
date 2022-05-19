#include "CWidget_Canvas.h"
#include "Cerberus/Core/Utility/CameraManager/CameraManager.h"
#include "Cerberus/Core/UI/CWidget_Button.h"
#include "Cerberus/Core/Utility/Math/Math.h"


CWidget_Canvas::CWidget_Canvas()
{
	InitialiseCanvas();
}



void CWidget_Canvas::InitialiseCanvas()
{
	
}

void CWidget_Canvas::Update(float deltaTime)
{

	
	for (int i = 0; i < buttonList.size(); i++)
	{
		if (buttonList[i] != nullptr)
		{
			buttonList[i]->IsButtonFocused(GetMousePosition());

			if (Inputs::InputManager::IsMouseButtonPressed(Inputs::InputManager::Mouse::LButton))
			{
				buttonList[i]->ButtonPressed(true);
			}
			else if (Inputs::InputManager::IsMouseButtonReleased(Inputs::InputManager::Mouse::LButton))
			{
				buttonList[i]->ButtonPressed(false);
			}
		}

	}
	



}

Vector2 CWidget_Canvas::GetMousePosition()
{

	Vector3 tempPos = Vector3(Inputs::InputManager::mousePos.x - Engine::windowWidth * 0.5f, -Inputs::InputManager::mousePos.y + Engine::windowHeight * 0.5f, GetPosition().z);
	return Vector2(tempPos.x, tempPos.y);
}

void CWidget_Canvas::RecievedUIEvent(int EventID)
{
	switch (EventID)
	{
	case 0:
		//Example
		break;
	}
}

CWidget_Button* CWidget_Canvas::CreateButton(Vector2 Position, Vector2 Scale, std::string ButtonName, int ID)
{
	CWidget_Button* Button = Engine::CreateEntity<CWidget_Button>();
	Button->SetText(ButtonName);
	Button->SetWidgetTransform(Position, Vector2(0,0), 1);
	Button->SetSlot(ID);
	buttonList.push_back(Button);
	AddChild(Button);
	return Button;
}

void CWidget_Canvas::SetVisibility(bool IsVisible)
{
	for (int i = 0; i < GetChildren().size(); i++)
	{
		GetChildren()[i]->SetVisibility(IsVisible);
	}


}
