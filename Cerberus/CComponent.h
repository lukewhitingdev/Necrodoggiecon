#pragma once
#include "CObject.h"

class CComponent : public CObject
{
public:
	XMFLOAT3 position = { 0,0,0 };
	XMFLOAT3 scale = { 1,1,1 };
	float rotation = 0;
	bool shouldDraw = false;
public:
	virtual void Update(float deltaTime) override = 0;
	virtual void Draw() = 0;
	virtual ~CComponent() {};
};