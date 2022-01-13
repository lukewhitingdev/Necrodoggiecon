#pragma once
#include "CObject.h"
#include "Engine.h"

class CComponent : public CObject
{
protected:
	XMFLOAT4X4 world;
public:
	XMFLOAT3 position = { 0,0,0 };
	XMFLOAT3 scale = { 1,1,1 };
	float rotation = 0;
	bool shouldDraw = false;
public:
	virtual void Update(float deltaTime) override = 0;
	virtual void Draw(struct ID3D11DeviceContext* context) = 0;
	virtual ~CComponent() {};

	virtual XMFLOAT4X4 GetTransform()
	{
		XMMATRIX mat = XMMatrixScaling(scale.x, scale.y, scale.z)
			* XMMatrixRotationRollPitchYaw(0, 0, rotation)
			* XMMatrixTranslation(position.x, position.y, position.z);

		XMStoreFloat4x4(&world, mat);
		return world;
	}
};