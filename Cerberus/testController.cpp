#include "testController.h"
#include "testCharacter.h"
void testController::Update(float deltaTime)
{
	HandleInput(deltaTime);
}

void testController::HandleInput(float deltaTime)
{
	if (!HasCharacter()) return;
	
	if (Input::GetKeyState(Keys::D))
		dynamic_cast<IInputable*>(GetCharacter())->PressedHorizontal(1, deltaTime);
	if (Input::GetKeyState(Keys::A))
		dynamic_cast<IInputable*>(GetCharacter())->PressedHorizontal(-1, deltaTime);
	if (Input::GetKeyState(Keys::W))
		dynamic_cast<IInputable*>(GetCharacter())->PressedVertical(1, deltaTime);
	if (Input::GetKeyState(Keys::S))
		dynamic_cast<IInputable*>(GetCharacter())->PressedVertical(-1, deltaTime);
	if (Input::GetKeyState(Keys::E))
		SwapChar();
}

void testController::SwapChar()
{
	if (charIndex == 1)
	{
		Possess(charTwo);
		charIndex = 2;
	}
	else if (charIndex == 2)
	{
		Possess(charOne);
		charIndex = 1;
	}
}
