#include "BoundingSphere.h"

BoundingCircle::BoundingCircle() : CollisionComponent()
{


}

bool BoundingCircle::IsColliding(CollisionComponent* collidingObject)
{
	switch (collidingObject->GetCollisionType())
	{
		case COLLISIONTYPE::BOUNDING_CIRCLE:
		{
			Vector3 otherPos = collidingObject->GetPosition();
			Vector3 thisPos = GetPosition();
			otherPos.z = 0;
			thisPos.z = 0;
			if (distanceBetweenPoints(thisPos, otherPos) < (radius + ((BoundingCircle*)collidingObject)->radius))
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
	return false;
}

void BoundingCircle::SetRadius(float radius1)
{
	radius = radius1;
}

float BoundingCircle::GetRadius()
{
	return radius;
}

void BoundingCircle::Update(float deltaTime)
{
	std::cout << "radius: " << radius << std::endl;
}

float BoundingCircle::distanceBetweenPoints(Vector3& point1, Vector3& point2)
{
	float distance = sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y) + (point1.z - point2.z) * (point1.z - point2.z));
	return distance;
}
