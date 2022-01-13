#pragma once
// Basic Object with world position.

#include "CObject.h"
#include "CComponent.h"

class CEntity : public CObject
{
protected:
	XMFLOAT4X4 world;
public:
	XMFLOAT3 position = {0,0,0};
	XMFLOAT3 scale = {1,1,1};
	float rotation = 0;

	std::vector<CComponent*> components;

	virtual void Update(float deltaTime) override = 0;
	virtual ~CEntity() 
	{
		for (auto& e : components)
			delete e;
	};

	virtual XMFLOAT4X4 GetTransform()
	{
		XMMATRIX mat = XMMatrixScaling(scale.x, scale.y, scale.z)
			* XMMatrixRotationRollPitchYaw(0, 0, rotation)
			* XMMatrixTranslation(position.x, position.y, position.z);

		XMStoreFloat4x4(&world, mat);
		return world;
	}
};