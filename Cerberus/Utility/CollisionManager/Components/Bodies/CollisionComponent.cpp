#include "CollisionComponent.h"

CollisionComponent::CollisionComponent()
{
	collisionType = BOUNDING_CIRCLE;

	//test = AddComponent<CEntity>();

}

CollisionComponent::~CollisionComponent()
{

}

COLLISIONTYPE CollisionComponent::GetCollisionType()
{
	return collisionType;
}

void CollisionComponent::SetBoundingType(COLLISIONTYPE collisionType1)
{
	collisionType = collisionType1;
}

COLLISIONTYPE CollisionComponent::GetBoundingType()
{
	return COLLISIONTYPE();
}

bool CollisionComponent::IsColliding(CollisionComponent* collidingObject)
{
	switch (collidingObject->GetCollisionType())
	{
	case BOUNDING_CIRCLE:
	{
		Vector3 otherPos = collidingObject->test->GetPosition();
		Vector3 thisPos = test->GetPosition();
		otherPos.z = 0;
		thisPos.z = 0;
		if (distanceBetweenPoints(thisPos, otherPos) < (radius + (collidingObject)->radius))
		{
			return true;
		}
		break;
	}
	case BOUNDING_BOX:
	{
		break;
	}
	}
	return false;
}

float CollisionComponent::distanceBetweenPoints(Vector3& point1, Vector3& point2)
{
	float distance = sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y) + (point1.z - point2.z) * (point1.z - point2.z));
	return distance;
}

void CollisionComponent::Update(float deltaTime)
{
}
