#include "CComponent.h"
#include "CEntity.h"

void CComponent::SetParent(CEntity* newParent)
{
	parent = newParent;
}

XMFLOAT4X4 CComponent::GetTransform()
{
	if (!ui)
	{
		if (updateTransform)
		{
			Vector3 scale = GetScale();
			Vector3 position = GetPosition();
			float rotation = GetRotation();

			XMMATRIX mat = XMMatrixScaling(scale.x, scale.y, scale.z)
				* XMMatrixRotationRollPitchYaw(0, 0, rotation)
				* XMMatrixTranslation(position.x, position.y, position.z);

			XMStoreFloat4x4(&world, mat);

			updateTransform = false;
		}

		return world;
	}

	if (updateTransform && ui || lastResolution.x != Engine::windowWidth || lastResolution.y != Engine::windowHeight)
	{
		lastResolution.x = Engine::windowWidth;
		lastResolution.y = Engine::windowHeight;

		Vector3 scale = GetScale();
		Vector3 position = GetPosition();
		float rotation = GetRotation();

		XMFLOAT2 anchorNorm = XMFLOAT2(anchor.x * 2 - 1, anchor.y * -2 + 1);

		XMFLOAT2 anchPoint = XMFLOAT2((anchorNorm.x * (Engine::windowWidth - 1280.0f) * .5),
			(anchorNorm.y * (Engine::windowHeight - 720.0f) * .5));

		XMFLOAT2 anchAdd = XMFLOAT2(position.x - anchPoint.x, position.y - anchPoint.y);

		XMMATRIX mat = XMMatrixScaling(scale.x, scale.y, scale.z)
			* XMMatrixRotationRollPitchYaw(0, 0, rotation)
			* XMMatrixTranslation(position.x + anchPoint.x, position.y + anchPoint.y, position.z);

		XMStoreFloat4x4(&world, mat);

		updateTransform = false;
	}

	return world;
}
