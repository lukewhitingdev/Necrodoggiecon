#pragma once
#include "CollisionComponent.h"

class BoundingCircle : public CollisionComponent
{
public:
	BoundingCircle();

	bool IsColliding(CollisionComponent* collidingObject);

	void SetRadius(float radius1);
	float GetRadius();

	float distanceBetweenPoints(Vector3& point1, Vector3& point2);

protected:
	float radius;
};

