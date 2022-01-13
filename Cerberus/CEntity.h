#pragma once

#include "CComponent.h"

////Fundimental class of the engine with a world transform and ability to have components
//Use for all gameplay things in the world
class CEntity
{
protected:
	XMFLOAT4X4 world;
public:
	bool shouldUpdate = true;
	XMFLOAT3 position = {0,0,0};
	XMFLOAT3 scale = {1,1,1};
	float rotation = 0;

	std::vector<CComponent*> components;

	//Updated automatically every single frame
	virtual void Update(float deltaTime) = 0;
	virtual ~CEntity();

	//Convert pos, scale and rot to a XMFloat4x4
	virtual XMFLOAT4X4 GetTransform();
};