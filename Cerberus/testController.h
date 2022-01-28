#pragma once
#include <CPlayerController.h>

class IInputable;

class testController : public CPlayerController
{
public:
	virtual void Update(float deltaTime) override;

	CCharacter* charOne = nullptr;
	CCharacter* charTwo = nullptr;

protected:
	virtual void HandleInput(float deltaTime) override;
	int charIndex = 1;
	void SwapChar();

	IInputable* inputable = nullptr;

	virtual void OnPossess() override;
	virtual void OnUnpossess() override;
};

