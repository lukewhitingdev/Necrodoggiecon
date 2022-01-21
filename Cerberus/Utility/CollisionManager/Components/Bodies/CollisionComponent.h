#pragma once
#include "CEntity.h"
#include "CComponent.h"
#include <thread>
	
enum class COLLISIONTYPE 
{
	BOUNDING_BOX,
	BOUNDING_CIRCLE
};


//A component for collisions
class CollisionComponent
{
public:
	CollisionComponent();
	virtual ~CollisionComponent();

	COLLISIONTYPE GetCollisionType();
	CEntity* test = nullptr;
	
	void SetBoundingType(COLLISIONTYPE collisionType1);
	COLLISIONTYPE GetBoundingType();

	bool IsColliding(CollisionComponent* collidingObject);
	float distanceBetweenPoints(Vector3& point1, Vector3& point2);

private: 
	float radius;
	COLLISIONTYPE collisionType = COLLISIONTYPE::BOUNDING_CIRCLE;

	//std::thread* collisionThread = nullptr;
};

