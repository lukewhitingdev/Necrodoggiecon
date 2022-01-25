#pragma once
#include <CCharacter.h>
#include <IInputable.h>

class testCharacter : public CCharacter, public IInputable
{
protected:
	float speed = 200;
	float timeElapsed = 0;
public:
	testCharacter();

	void PressedHorizontal(int dir, float deltaTime) override;
	void PressedVertical(int dir, float deltaTime) override;

	virtual void Update(float deltaTime) override;
	virtual void HasCollided(CollisionComponent* collided) override;
};

