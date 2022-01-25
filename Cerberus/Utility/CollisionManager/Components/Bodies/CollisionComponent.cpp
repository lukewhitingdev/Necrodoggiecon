#include "CollisionComponent.h"

CollisionComponent::CollisionComponent() 
{
	collisionType = COLLISIONTYPE::BOUNDING_CIRCLE;

	//test = AddComponent<CEntity>();

};

CollisionComponent::~CollisionComponent()
{

}

COLLISIONTYPE CollisionComponent::GetCollisionType()
{
	return collisionType;
}

float CollisionComponent::GetRadius()
{
	return radius;
}

void CollisionComponent::SetRadius(float setRadius)
{
	radius = setRadius;
}

void CollisionComponent::SetPosition(Vector3 setPosition)
{
	position = setPosition;
}

Vector3 CollisionComponent::GetPosition()
{
	return position;
}

//SetCollider overload for bounding circle
void CollisionComponent::SetCollider(float setRadius)
{
	collisionType = COLLISIONTYPE::BOUNDING_CIRCLE;
	radius = setRadius;
}
//SetCollider overload for bounding box
void CollisionComponent::SetCollider(float setHeight, float setWidth)
{
	collisionType = COLLISIONTYPE::BOUNDING_CIRCLE;
	height = setHeight;
	width = setWidth;
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
	if (collisionType == COLLISIONTYPE::BOUNDING_CIRCLE)
	{
		switch (collidingObject->GetCollisionType())
		{
			case COLLISIONTYPE::BOUNDING_CIRCLE:
			{
				Vector3 otherPos = collidingObject->GetPosition();
				Vector3 thisPos = position;
				otherPos.z = 0;
				thisPos.z = 0;
				if (distanceBetweenPoints(thisPos, otherPos) < (radius + (collidingObject)->radius))
				{
					return true;
				}
				break;
			}
			case COLLISIONTYPE::BOUNDING_BOX:
			{
				
				break;
			}
		}

	}
	else if (collisionType == COLLISIONTYPE::BOUNDING_BOX)
	{
		switch (collidingObject->GetCollisionType())
		{
			case COLLISIONTYPE::BOUNDING_CIRCLE:
			{
				Vector3 otherPos = collidingObject->GetPosition();
				Vector3 thisPos = position;
				otherPos.z = 0;
				thisPos.z = 0;
				if (distanceBetweenPoints(thisPos, otherPos) < (radius + (collidingObject)->radius))
				{
					return true;
				}
				break;
			}
			case COLLISIONTYPE::BOUNDING_BOX:
			{
				Vector3 otherPos = collidingObject->GetPosition();
				Vector3 thisPos = position;
				otherPos.z = 0;
				thisPos.z = 0;
				if ((thisPos.x - width / 2 <= otherPos.x + collidingObject->width / 2 && thisPos.x + width / 2 >= otherPos.x - collidingObject->width / 2) && 
					(thisPos.y + height / 2 <= otherPos.y - collidingObject->height / 2 && thisPos.y - height / 2 >= otherPos.y + collidingObject->height / 2))
				{
					Debug::Log("BOUNDINGBOX COLLISION");
				}
				break;
			}
		}
	}
	return false;
}

float CollisionComponent::distanceBetweenPoints(Vector3& point1, Vector3& point2)
{
	float distance = sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y) + (point1.z - point2.z) * (point1.z - point2.z));
	return distance;
}
