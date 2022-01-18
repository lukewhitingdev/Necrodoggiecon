#include "BoundingSphere.h"

BoundingCircle::BoundingCircle() : CollisionComponent(BOUNDING_CIRCLE)
{


}

bool BoundingCircle::IsColliding(CollisionComponent* collidingObject)
{
	switch (collidingObject->GetCollisionType())
	{
		case BOUNDING_CIRCLE:
		{
			Vector3 otherPos = collidingObject->test->GetPosition();
			Vector3 thisPos = test->GetPosition();
			otherPos.z = 0;
			thisPos.z = 0;
			if (distanceBetweenPoints(thisPos, otherPos) < (radius + ((BoundingCircle*)collidingObject)->radius))
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

void BoundingCircle::SetRadius(float radius1)
{
	radius = radius1;
}

float BoundingCircle::GetRadius()
{
	return radius;
}

float BoundingCircle::distanceBetweenPoints(Vector3& point1, Vector3& point2)
{
	float distance = sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y) + (point1.z - point2.z) * (point1.z - point2.z));
	return distance;
}
