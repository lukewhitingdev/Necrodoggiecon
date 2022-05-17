#include "CWidget_Canvas.h"
#include "Cerberus/Core/Utility/CameraManager/CameraManager.h"
#include "Cerberus/Core/UI/CWidget_Button.h"


CWidget_Canvas::CWidget_Canvas()
{
}

void CWidget_Canvas::InitialiseCanvas()
{
	
}

void CWidget_Canvas::Update(float deltaTime)
{

	
	for (int i = 0; i < buttonList.size(); i++)
	{
		buttonList[i]->IsButtonFocused(GetMousePosition());
		if (Inputs::InputManager::IsMouseButtonReleased(Inputs::InputManager::Mouse::LButton))
		{
			buttonList[i]->ButtonTriggered();
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

void CWidget_Canvas::CreateButton(Vector2 Position, Vector2 Scale, std::string ButtonName, int ID)
{
	CWidget_Button* Button = Engine::CreateEntity<CWidget_Button>();
	Button->SetText(ButtonName);
	Button->SetPosition(Position.x, Position.y, -2);
	Button->SetSlot(ID);
	buttonList.push_back(Button);
}
