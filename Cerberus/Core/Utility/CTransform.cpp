#include "Utility/CTransform.h"

XMFLOAT4X4 CTransform::GetTransform()
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