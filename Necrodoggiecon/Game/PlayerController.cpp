#include "PlayerController.h"

#include "ItemDatabase.h"
#include "CEquippedItem.h"

#include <Necrodoggiecon\Game\CursorEntity.h>
#include <Necrodoggiecon\Game\AI/CAICharacter.h>


PlayerController::PlayerController()
{
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
	if (Inputs::InputManager::IsKeyPressedDown(Inputs::InputManager::Q))
		inputable->PressedUse();

	if (Inputs::InputManager::IsMouseButtonPressed(Inputs::InputManager::Mouse::LButton))
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
