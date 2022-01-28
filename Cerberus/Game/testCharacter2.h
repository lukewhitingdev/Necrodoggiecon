#pragma once
#include <IInputable.h>
#include <CCharacter.h>

class testCharacter2 : public CCharacter, public IInputable
{
protected:
	float speed = 200;
public:
	testCharacter2();

	void PressedHorizontal(int dir, float deltaTime) override;
	void PressedVertical(int dir, float deltaTime) override;

	virtual void Update(float deltaTime) override;

	// Inherited via IInputable
	virtual void PressedInteract() override;
	virtual void PressedDrop() override;
};

