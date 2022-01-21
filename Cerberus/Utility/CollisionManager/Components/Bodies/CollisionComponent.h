#pragma once
//#include "CEntity.h"
#include "Vector3.h"
#include "Utility/DebugOutput/Debug.h"
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

	~CollisionComponent();

	COLLISIONTYPE GetCollisionType();
	//CEntity* test = nullptr;
	
	float GetRadius();
	void SetRadius(float setRadius);

	void SetPosition(Vector3 setPosition);
	Vector3 GetPosition();

	void SetBoundingType(COLLISIONTYPE collisionType1);
	COLLISIONTYPE GetBoundingType();

	bool IsColliding(CollisionComponent* collidingObject);
	float distanceBetweenPoints(Vector3& point1, Vector3& point2);

private: 
	float radius;
	Vector3 position;
	COLLISIONTYPE collisionType = COLLISIONTYPE::BOUNDING_CIRCLE;

	//std::thread* collisionThread = nullptr;
};

