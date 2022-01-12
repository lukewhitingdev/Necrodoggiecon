#pragma once
//Basic class that does not have a world position.

class CObject
{
public:
	bool shouldUpdate = true;
public:
	virtual void Update(float deltaTime) = 0;
	virtual ~CObject() {};
};