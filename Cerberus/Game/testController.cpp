#include "testController.h"
#include "testCharacter.h"
#include "ItemDatabase.h"
#include "CEquippedItem.h"

#include <Cerberus\Game\CursorEntity.h>
#include <Cerberus\Game\AI/CAICharacter.h>

void testController::Update(float deltaTime)
{
	HandleInput(deltaTime);
}

void testController::HandleInput(float deltaTime)
{
	if (!HasCharacter()) return;
	
	if (inputable == nullptr) return;


	if (Inputs::InputManager::IsKeyPressed(Inputs::InputManager::D))
		inputable->PressedHorizontal(1, deltaTime);
	if (Inputs::InputManager::IsKeyPressed(Inputs::InputManager::A))
		inputable->PressedHorizontal(-1, deltaTime);
	if (Inputs::InputManager::IsKeyPressed(Inputs::InputManager::W))
		inputable->PressedVertical(1, deltaTime);
	if (Inputs::InputManager::IsKeyPressed(Inputs::InputManager::S))
		inputable->PressedVertical(-1, deltaTime);
	if (Inputs::InputManager::IsKeyPressedDown(Inputs::InputManager::E))
		inputable->PressedInteract();
	if (Inputs::InputManager::IsKeyPressedDown(Inputs::InputManager::G))
		inputable->PressedDrop();


	if (Inputs::InputManager::IsKeyPressedDown(Inputs::InputManager::Q))
	{
		//EquippedItem* item = ItemDatabase::Instance()->CreateItemFromID(0);
		//testCharacter* item = Engine::CreateEntity<testCharacter>();
		CursorEntity* item = Engine::CreateEntity<CursorEntity>();
		//CAICharacter* item = Engine::CreateEntity<CAICharacter>();
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

void testController::OnPossess()
{
	inputable = dynamic_cast<IInputable*>(GetCharacter());
}

void testController::OnUnpossess()
{
	inputable = nullptr;
}
