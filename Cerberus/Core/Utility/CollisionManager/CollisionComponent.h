#pragma once
#include "Cerberus\Core\Utility\Vector3.h"
#include "Cerberus/Core/Utility/DebugOutput/Debug.h"
#include <thread>
	
enum class COLLISIONTYPE 
{
	BOUNDING_BOX,
	BOUNDING_CIRCLE,
	BOUNDING_NONE
};


class CEntity;

//A component for collisions
class CollisionComponent
{
public:
	CollisionComponent(std::string setName, CEntity* parent);

	~CollisionComponent();

	COLLISIONTYPE GetCollisionType();
	
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

	CEntity* GetParent();

private: 
	float radius;
	Vector3 position;
	float height;
	float width;
	std::string name = "none";

	CEntity* parent = nullptr;

	COLLISIONTYPE collisionType = COLLISIONTYPE::BOUNDING_NONE;
};

