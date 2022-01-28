#pragma once

class IInputable
{
public:
	virtual void PressedHorizontal(int dir, float deltaTime) = 0;
	virtual void PressedVertical (int dir, float deltaTime) = 0;
	virtual void PressedInteract() = 0;
	virtual void PressedDrop() = 0;
};