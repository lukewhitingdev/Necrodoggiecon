#include "CComponent.h"

XMFLOAT4X4 CComponent::GetTransform()
{
	if (bUpdateTransform)
	{
		XMMATRIX mat = XMMatrixScaling(scale.x, scale.y, scale.z)
			* XMMatrixRotationRollPitchYaw(0, 0, rotation)
			* XMMatrixTranslation(position.x, position.y, position.z);

		XMStoreFloat4x4(&world, mat);

		bUpdateTransform = false;
	}

	return world;
}