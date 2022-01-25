#include "CEntity.h"

CEntity::~CEntity()
{
	for (auto& e : components)
		delete e;
}

void CEntity::SetCollider()
{
	GetPosition();
}

void CEntity::HasCollided()
{
	Debug::Log("CEntity Collision!!!!!");
}

