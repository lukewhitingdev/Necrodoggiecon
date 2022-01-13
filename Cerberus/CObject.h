#pragma once
//Basic class that does not have a world position.

//Fundimental class of the engine
//Use for managers and other things that don't exist in world space
class CObject
{
public:
	bool shouldUpdate = true;
public:
	//Updated automatically every single frame
	virtual void Update(float deltaTime) = 0;
	virtual ~CObject() {};
};