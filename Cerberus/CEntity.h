#pragma once

#include "CComponent.h"
#include "Utility/CollisionManager/CollisionComponent.h"
#include "Vector3.h"

////Fundimental class of the engine with a world transform and ability to have components
//Use for all gameplay things in the world
class CEntity : public CTransform
{

public:
	bool shouldUpdate = true;
	bool shouldMove = false;
	bool visible = true;

	std::vector<CComponent*> components;
	
	//Updated automatically every single frame
	virtual void Update(float deltaTime) = 0;
	virtual ~CEntity();

	template <class T>
	T* AddComponent()
	{
		CComponent* tmp = new T();
		tmp->SetParent(this);
		components.push_back(tmp);
		return dynamic_cast<T*>(tmp);
	}

	// Removes the specified component.
	void RemoveComponent(CComponent* reference);
	CollisionComponent* colComponent = nullptr;
	virtual void HasCollided(CollisionComponent* collidedObject) { UNREFERENCED_PARAMETER(collidedObject); };
};