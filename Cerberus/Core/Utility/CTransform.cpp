#include "Cerberus/Core/Utility/CTransform.h"
#include "Cerberus/Core/Utility/DebugOutput/Debug.h"

void CTransform::SetRotation(const float& Rot)
{
	if (!std::isnan(Rot))
	{
		rotation = Rot;
	}
	else
	{
		rotation = 0;
		Debug::LogError("Set rotation value is NaN!");
	}

	updateTransform = true;
}

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