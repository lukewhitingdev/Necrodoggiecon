#include "PlayerController.h"

#include "ItemDatabase.h"
#include "CEquippedItem.h"

#include <Necrodoggiecon\Game\CursorEntity.h>
#include <Necrodoggiecon\Game\AI/CAICharacter.h>


PlayerController::PlayerController()
{
}

void PlayerController::Update(float deltaTime)
{
	HandleInput(deltaTime);
}

void PlayerController::HandleInput(float deltaTime)
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
	if (Inputs::InputManager::IsKeyPressedDown(Inputs::InputManager::L))
		charOne->loadNoise->Play();

	if (Inputs::InputManager::IsMouseButtonPressed(Inputs::InputManager::Mouse::LButton))
		inputable->Attack();

	if (Inputs::InputManager::IsKeyPressedDown(Inputs::InputManager::Q))
	{
		CursorEntity* item = Engine::CreateEntity<CursorEntity>();
		item->SetPosition(Vector3((float(rand() % Engine::windowWidth) - Engine::windowWidth / 2), (float(rand() % Engine::windowHeight) - Engine::windowHeight / 2), 0));
	}
}

void PlayerController::OnPossess()
{
	inputable = dynamic_cast<IInputable*>(GetCharacter());
}

void PlayerController::OnUnpossess()
{
	inputable = nullptr;
}
