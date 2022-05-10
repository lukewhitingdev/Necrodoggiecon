#pragma once
//#include "Cerberus\Core\CEntity.h"
#include "Cerberus\Core\Utility\Vector3.h"
#include "Cerberus/Core/Utility/DebugOutput/Debug.h"
#include <thread>
	
enum class COLLISIONTYPE 
{
	BOUNDING_BOX,
	BOUNDING_CIRCLE,
	BOUNDING_NONE
};


//A component for collisions
class CollisionComponent
{
public:
	CollisionComponent(std::string setName);

	~CollisionComponent();

	COLLISIONTYPE GetCollisionType();
	//CEntity* test = nullptr;
	
	float GetRadius();
	void SetRadius(float setRadius);

	void SetPosition(Vector3 setPosition);
	Vector3 GetPosition();

	std::string GetName() { return name; };

	float GetWidth() { return width; };
	float GetHeight() { return height; };

	bool Intersects(CollisionComponent* circle, CollisionComponent* box);

	void SetCollider(float setRadius); //Bounding circle initiation
	void SetCollider(float setHeight, float setWidth); //Bounding Box initiation


	bool IsColliding(CollisionComponent* collidingObject);
	float DistanceBetweenPoints(Vector3& point1, Vector3& point2);

private: 
	float radius;
	Vector3 position;
	float height;
	float width;
	std::string name = "none";

	COLLISIONTYPE collisionType = COLLISIONTYPE::BOUNDING_NONE;
};

