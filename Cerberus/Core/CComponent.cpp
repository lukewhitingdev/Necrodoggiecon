#include "Cerberus\Core\CComponent.h"
#include "Cerberus\Core\CEntity.h"

void CComponent::SetParent(CEntity* newParent)
{
	parent = newParent;
}

void CComponent::SetUseTranslucency(const bool& newTranslucency)
{
	//This looks weird, but basically moves the component from one container to another.
	EntityManager::RemoveComponent(this);
	translucency = newTranslucency;
	EntityManager::AddComponent(this);
}

const std::string CComponent::GetDebugInfo() const
{
	std::string output = "";
	output.append(GetName());

	if (GetParent() != nullptr)
	{
		output.append(" in ");
		output.append(GetParent()->GetName());
	}

	return output;
}

XMFLOAT3 CComponent::GetWorldPosition()
{
	//Not ideal, but it works for the current setup.
	XMFLOAT4X4 ivalue = GetTransform();
	XMMATRIX mat = XMLoadFloat4x4(&ivalue);
	ivalue = GetParent()->GetTransform();
	XMMATRIX mat2 = XMLoadFloat4x4(&ivalue);
	XMVECTOR pos = { 0,0,0,0 };
	pos = XMVector3Transform(pos, mat * mat2);
	XMFLOAT3 result;
	XMStoreFloat3(&result, pos);

	return result;
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
