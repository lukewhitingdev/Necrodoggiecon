#pragma once
#include <Necrodoggiecon\Game\CPlayerController.h>
#include "Cerberus/Core/Components/CAudioEmitterComponent.h"

class IInputable;

class PlayerController : public CPlayerController
{
public:
	PlayerController();
	virtual void Update(float deltaTime) override;

	CCharacter* charOne = nullptr;

protected:
	virtual void HandleInput(float deltaTime) override;
	int charIndex = 1;

	IInputable* inputable = nullptr;

	virtual void OnPossess() override;
	virtual void OnUnpossess() override;

	CAudioEmitterComponent* loadNoise;
};

