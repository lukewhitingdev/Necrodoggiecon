#pragma once
#include "CObject.h"
#include "Engine.h"

class CComponent : public CObject
{
public:
	XMFLOAT3 position = { 0,0,0 };
	XMFLOAT3 scale = { 1,1,1 };
	float rotation = 0;
	bool shouldDraw = false;
public:
	virtual void Update(float deltaTime) override = 0;
	virtual void Draw(struct ID3D11DeviceContext* context) = 0;
	virtual ~CComponent() {};
};