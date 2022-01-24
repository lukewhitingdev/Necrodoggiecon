#include "CPlayerController.h"

CPlayerController::CPlayerController()
{
}

CPlayerController::~CPlayerController()
{
	possessedCharacter = nullptr;
	delete possessedCharacter;
}

void CPlayerController::Possess(CCharacter* characterToPossess)
{
	if (hasCharacter)
		Unpossess();

	possessedCharacter = characterToPossess;
	hasCharacter = true;

}

void CPlayerController::Unpossess()
{
	possessedCharacter = nullptr;
	hasCharacter = false;
}

void CPlayerController::HandleInput(float deltaTime)
{
}
