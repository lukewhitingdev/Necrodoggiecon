#include "Cerberus/Core/UI/CWidget_Button.h"
#include "Cerberus/Core/Components/CSpriteComponent.h"
#include "Cerberus/Core/UI/CWidget_Canvas.h"

CWidget_Button::CWidget_Button()
{

}

void CWidget_Button::SetSlot(int Slot)
{

}

void CWidget_Button::SetText(std::string TextBody)
{
}

void CWidget_Button::SetSize(Vector2 Size)
{
}

void CWidget_Button::OnButtonPressed()
{
}

void CWidget_Button::OnButtonReleased()
{
}

void CWidget_Button::OnButtonHoverStart()
{
}

void CWidget_Button::OnButtonHoverEnd()
{
}

void CWidget_Button::IsButtonFocused(Vector2 mPos)
{

	Vector2 Scale = Vector2(sprite->GetSpriteSize().x, sprite->GetSpriteSize().y);
	Vector2 Pos = Vector2(GetPosition().x, GetPosition().y);
	if (!hasFocus)
	{
		if (mPos.x > Pos.x && mPos.x < Scale.x + Pos.x &&
			mPos.y > Pos.y && mPos.y < Scale.y + Pos.y)
		{

			hasFocus = true;
			OnButtonHoverStart();
			

		}

	}
	else
	{
		if (!(mPos.x > Pos.x && mPos.x < Scale.x + Pos.x &&
			mPos.y > Pos.y && mPos.y < Scale.y + Pos.y))
		{

			hasFocus = false;
			OnButtonHoverEnd();

		}
		

	}
}

void CWidget_Button::ButtonTriggered()
{
	if (hasFocus) OwningCanvas->RecievedUIEvent(buttonSlot);
}
