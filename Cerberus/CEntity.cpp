#include "CEntity.h"

CEntity::~CEntity()
{
	for (auto& e : components)
		delete e;
};

XMFLOAT4X4 CEntity::GetTransform()
{
	if (updateTransform)
	{
		XMMATRIX mat = XMMatrixScaling(scale.x, scale.y, scale.z)
			* XMMatrixRotationRollPitchYaw(0, 0, rotation)
			* XMMatrixTranslation(position.x, position.y, position.z);

		XMStoreFloat4x4(&world, mat);

		updateTransform = false;
	}

	return world;
}

// simple movement for a player
// note that due to this being called in main update only one key can be passed
Vector3 CEntity::Movement(float deltaTime)
{
	if (player)
	{

		float move = 100.0f;
		float speed = move * deltaTime;

		if (GetAsyncKeyState(0x44))
		{
			position.x -= speed;
			SetPosition(position);
			return position.x;
		}
		else if (GetAsyncKeyState(0x41))
		{
			position.x += speed;
			SetPosition(position);
			return position.x;
		}
		else if (GetAsyncKeyState(0x57))
		{
			position.y += speed;
			SetPosition(position);
			return position.y;
		}
		else if (GetAsyncKeyState(0x53))
		{
			position.y -= speed;
			SetPosition(position);
			return position.y;
		}
	}
}