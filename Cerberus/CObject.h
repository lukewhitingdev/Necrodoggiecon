#pragma once

class CObject
{
public:
	bool shouldUpdate = true;
public:
	virtual void Update(float deltaTime) = 0;
	virtual ~CObject() {};
};