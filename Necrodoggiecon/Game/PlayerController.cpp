#include "PlayerController.h"

#include <Necrodoggiecon\Game\CursorEntity.h>

#include <Game/DialogueHandler.h>
#include <Cerberus/Core/Utility/EventSystem/EventSystem.h>

PlayerController::PlayerController()
{
	EventSystem::AddListener("DialogueOpen", std::bind(&PlayerController::OnDialogueOpen, this));
	EventSystem::AddListener("DialogueClose", std::bind(&PlayerController::OnDialogueClose, this));
}

/**
 * Inherited function
 * Used to update the Controller each frame
 * \param deltaTime - Time since the last frame
 */
void PlayerController::Update(float deltaTime)
{
	HandleInput(deltaTime);
}

/**
 * Inherited function
 * Used to handle the input that the Controller receives
 * Will pass input down to the possessed Character using the IInputable interface
 * 
 * \param deltaTime - Time since the last frame
 */
void PlayerController::HandleInput(float deltaTime)
{
	if (dialogueOpen)
	{
		if (InputManager::IsMouseButtonPressedDown(InputManager::Mouse::LButton))
		{
			buttonHeld = true;
		}
		if (InputManager::IsKeyPressedDown(InputManager::E))
			DialogueHandler::AdvanceDialogue();
		if (InputManager::IsMouseButtonReleased(InputManager::Mouse::LButton) && buttonHeld)
			DialogueHandler::AdvanceDialogue();
		return;
	}

	if (!HasCharacter()) return;
	
	if (inputable == nullptr) return;

	if (InputManager::IsKeyPressed(InputManager::D))
		inputable->PressedHorizontal(1, deltaTime);
	if (InputManager::IsKeyPressed(InputManager::A))
		inputable->PressedHorizontal(-1, deltaTime);
	if (InputManager::IsKeyPressed(InputManager::W))
		inputable->PressedVertical(1, deltaTime);
	if (InputManager::IsKeyPressed(InputManager::S))
		inputable->PressedVertical(-1, deltaTime);
	if (InputManager::IsKeyPressedDown(InputManager::F))
		inputable->PressedInteract();
	if (InputManager::IsKeyPressedDown(InputManager::G))
		inputable->PressedDrop();
	if (InputManager::IsKeyPressedDown(InputManager::Q))
		inputable->PressedUse();

	if (InputManager::IsMouseButtonPressed(InputManager::Mouse::LButton))
		inputable->Attack();

}

/**
* Inherited function
* Used to get the IInputable interface from the newly possessed character
*/
void PlayerController::OnPossess()
{
	inputable = dynamic_cast<IInputable*>(GetCharacter());
}

/**
* Inherited function
* Used to remove the IInputable interface
*/
void PlayerController::OnUnpossess()
{
	inputable = nullptr;
}
