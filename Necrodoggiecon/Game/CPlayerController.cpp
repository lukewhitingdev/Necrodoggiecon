#include "CPlayerController.h"
/*****************************************************************//**
 * \file   CPlayerController.cpp
 * \brief  Base class for PlayerControllers, handles functionality for possessing and unpossessing characters.
 *
 *
 * \author Cathan Bertram
 * \date   May 2022
 *********************************************************************/
CPlayerController::CPlayerController()
{
}

CPlayerController::~CPlayerController()
{
	Engine::DestroyEntity((CEntity*)possessedCharacter);
	possessedCharacter = nullptr;
}
/**
* Function used to possess a new Character
* Will Unpossess the Controllers current Character and then set the current Character to the Character that was passed in
*/
void CPlayerController::Possess(CCharacter* characterToPossess)
{
	if (hasCharacter)
		Unpossess();

	possessedCharacter = characterToPossess;
	hasCharacter = true;

	OnPossess();
}
/**
* Function used to unpossess a Character
* Will remove all data associated with the current Character from the Controller
*/
void CPlayerController::Unpossess()
{
	possessedCharacter = nullptr;
	hasCharacter = false;

	OnUnpossess();
}
/**
* Virtual function used to handle the input that the controller receives
*/
void CPlayerController::HandleInput(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}
