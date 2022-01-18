#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(COLLISIONTYPE collisionType1)
{
	collisionType = collisionType;

	test = AddComponent<CEntity>();
}

CollisionComponent::~CollisionComponent()
{

}

COLLISIONTYPE CollisionComponent::GetCollisionType()
{
	return collisionType;
}

void CollisionComponent::Start()
{

}

void CollisionComponent::Update(float deltaTime)
{

}
