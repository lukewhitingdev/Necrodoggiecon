#include "CEntity.h"




CEntity::~CEntity()
{
	for (auto& e : components)
		delete e;
};

XMFLOAT4X4 CEntity::GetTransform()
{
	XMMATRIX mat = XMMatrixScaling(scale.x, scale.y, scale.z)
		* XMMatrixRotationRollPitchYaw(0, 0, rotation)
		* XMMatrixTranslation(position.x, position.y, position.z);

	XMStoreFloat4x4(&world, mat);
	return world;
}
