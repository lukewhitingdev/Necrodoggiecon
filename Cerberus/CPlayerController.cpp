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

	OnPossess();
}

void CPlayerController::Unpossess()
{
	possessedCharacter = nullptr;
	hasCharacter = false;

	OnUnpossess();
}

void CPlayerController::HandleInput(float deltaTime)
{
}
