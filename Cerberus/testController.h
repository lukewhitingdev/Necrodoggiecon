#pragma once
#include <CPlayerController.h>

class testController : public CPlayerController
{
public:
	virtual void Update(float deltaTime) override;

	CCharacter* charOne;
	CCharacter* charTwo;

protected:
	virtual void HandleInput(float deltaTime) override;
	int charIndex = 1;
	void SwapChar();
};

