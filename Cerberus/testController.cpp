#include "testController.h"
#include "testCharacter.h"
#include "InputManager.h"
#include "ItemDatabase.h"
#include "EquippedItem.h"
void testController::Update(float deltaTime)
{
	HandleInput(deltaTime);
}

void testController::HandleInput(float deltaTime)
{
	if (!HasCharacter()) return;
	
	if (Inputs::InputManager::IsKeyPressed(Inputs::InputManager::D))
		dynamic_cast<IInputable*>(GetCharacter())->PressedHorizontal(1, deltaTime);
	if (Inputs::InputManager::IsKeyPressed(Inputs::InputManager::A))
		dynamic_cast<IInputable*>(GetCharacter())->PressedHorizontal(-1, deltaTime);
	if (Inputs::InputManager::IsKeyPressed(Inputs::InputManager::W))
		dynamic_cast<IInputable*>(GetCharacter())->PressedVertical(1, deltaTime);
	if (Inputs::InputManager::IsKeyPressed(Inputs::InputManager::S))
		dynamic_cast<IInputable*>(GetCharacter())->PressedVertical(-1, deltaTime);
	if (Inputs::InputManager::IsKeyPressedDown(Inputs::InputManager::E))
		SwapChar();
	if (Inputs::InputManager::IsKeyPressedDown(Inputs::InputManager::Q))
	{
		EquippedItem* item = ItemDatabase::Instance()->CreateItemFromID(0);
		item->SetPosition(Vector3((float(rand() % Engine::windowWidth) - Engine::windowWidth / 2), (float(rand() % Engine::windowHeight) - Engine::windowHeight / 2), 0));
	}
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
