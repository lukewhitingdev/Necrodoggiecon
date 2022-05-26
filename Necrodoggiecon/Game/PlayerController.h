#pragma once
#include <Necrodoggiecon\Game\CPlayerController.h>
#include "PlayerCharacter.h"

class IInputable;

class PlayerController : public CPlayerController
{
public:
	PlayerController();
	virtual void Update(float deltaTime) override;

	PlayerCharacter* charOne = nullptr;

protected:
	virtual void HandleInput(float deltaTime) override;
	int charIndex = 1;

	IInputable* inputable = nullptr;

	virtual void OnPossess() override;
	virtual void OnUnpossess() override;

	bool dialogueOpen = false;

	void OnDialogueOpen() { dialogueOpen = true; }
	void OnDialogueClose() { dialogueOpen = false; }
};

