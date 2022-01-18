#pragma once
#include "CEntity.h"
#include "CComponent.h"
#include <thread>
	
enum COLLISIONTYPE
	{
		BOUNDING_BOX,
		BOUNDING_CIRCLE
	};

class CollisionComponent : public CComponent
{
public:
	CollisionComponent(COLLISIONTYPE collisionType1);
	~CollisionComponent();

	COLLISIONTYPE GetCollisionType();
	CEntity* test = nullptr;

	void Start();
	void Update(float deltaTime) override;

	std::vector<CComponent*> components;

	template <class T>
	T* AddComponent()
	{
		CComponent* tmp = new T();
		components.push_back(tmp);
		return dynamic_cast<T*>(tmp);
	}

private: 

	COLLISIONTYPE collisionType = BOUNDING_BOX;
	XMFLOAT3 BoundingBox;

	//std::thread* collisionThread = nullptr;
};

