#pragma once
#include "CObject.h"
#include "CComponent.h"

class CEntity : public CObject
{
public:
	XMFLOAT3 position = {0,0,0};
	XMFLOAT3 scale = {1,1,1};
	float rotation = 0;

	std::vector<CComponent*> components;

	virtual void Update(float deltaTime) override = 0;
	virtual ~CEntity() {};
};