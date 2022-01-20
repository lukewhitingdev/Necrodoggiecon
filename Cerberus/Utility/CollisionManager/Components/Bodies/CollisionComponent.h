#pragma once
#include "CEntity.h"
#include "CComponent.h"
#include <thread>
	
enum COLLISIONTYPE
{
	BOUNDING_BOX = 0,
	BOUNDING_CIRCLE
};


//A component for collisions
class CollisionComponent : public CComponent
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
	virtual void Update(float deltaTime) override;

private: 
	float radius;
	COLLISIONTYPE collisionType = BOUNDING_BOX;

	//std::thread* collisionThread = nullptr;
};

