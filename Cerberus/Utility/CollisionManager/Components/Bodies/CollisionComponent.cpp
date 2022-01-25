#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(std::string setName)
{
	collisionType = COLLISIONTYPE::BOUNDING_NONE;

	name = setName;
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

//Checks if a circle has intersected with a box
bool CollisionComponent::Intersects(CollisionComponent* circle, CollisionComponent* box)
{
	float distance = DistanceBetweenPoints(box->position, circle->position);

	if (distance > (box->width) + circle->radius || distance > (box->height) + circle->radius)
		return false;

	if (distance <= box->width || distance <= box->height)
		return true;

	return false;
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
	collisionType = COLLISIONTYPE::BOUNDING_BOX;
	height = setHeight;
	width = setWidth;
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
				if (DistanceBetweenPoints(thisPos, otherPos) < (radius + (collidingObject)->radius))
				{
					return true;
				}
				break;
			}
			case COLLISIONTYPE::BOUNDING_BOX:
			{
				if (Intersects(this, collidingObject))
				{
					return true;
				}
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
				if (Intersects(collidingObject, this))
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

				if (thisPos.x - (width / 2) <= otherPos.x + (collidingObject->GetWidth() / 2) && 
					thisPos.x + (width / 2) >= otherPos.x - (collidingObject->GetWidth() / 2) &&
					thisPos.y - (height / 2) <= otherPos.y + (collidingObject->GetHeight() / 2) && 
					thisPos.y + (height / 2) >= otherPos.y - (collidingObject->GetHeight() / 2))
				{
					return true;
				}
				break;
			}
		}
	}
	return false;
}

float CollisionComponent::DistanceBetweenPoints(Vector3& point1, Vector3& point2)
{
	float distance = sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y) + (point1.z - point2.z) * (point1.z - point2.z));
	return distance;
}
