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
			XMMATRIX mat = XMMatrixScaling(GetScale().x, GetScale().y, GetScale().z)
				* XMMatrixRotationRollPitchYaw(0, 0, GetRotation())
				* XMMatrixTranslation(GetPosition().x, GetPosition().y, GetPosition().z);

			XMStoreFloat4x4(&world, mat);

			updateTransform = false;
		}

		return world;
	}

	if (updateTransform && ui || lastResolution.x != Engine::windowWidth || lastResolution.y != Engine::windowHeight)
	{
		lastResolution.x = Engine::windowWidth;
		lastResolution.y = Engine::windowHeight;

		XMFLOAT2 anchorNorm = XMFLOAT2(anchor.x * 2.0f - 1.0f, anchor.y * -2.0f + 1.0f);

		XMFLOAT2 anchPoint = XMFLOAT2((anchorNorm.x * (float(Engine::windowWidth) - 1280.0f) * 0.5f),
			(anchorNorm.y * (Engine::windowHeight - 720.0f) * 0.5f));

		XMFLOAT2 anchAdd = XMFLOAT2(GetPosition().x - anchPoint.x, GetPosition().y - anchPoint.y);

		XMMATRIX mat = XMMatrixScaling(GetScale().x, GetScale().y, GetScale().z)
			* XMMatrixRotationRollPitchYaw(0, 0, GetRotation())
			* XMMatrixTranslation(GetPosition().x + anchPoint.x, GetPosition().y + anchPoint.y, GetPosition().z);

		XMStoreFloat4x4(&world, mat);

		updateTransform = false;
	}

	return world;
}
