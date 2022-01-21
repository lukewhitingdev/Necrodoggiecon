#pragma once

#include "CComponent.h"
#include "Vector3.h"
#include "Utility/CollisionManager/Components/Bodies/CollisionComponent.h"

////Fundimental class of the engine with a world transform and ability to have components
//Use for all gameplay things in the world
class CEntity : public CTransform
{

public:
	bool shouldUpdate = true;
	bool shouldMove = false;

	std::vector<CComponent*> components;

	//Updated automatically every single frame
	virtual void Update(float deltaTime) = 0;
	virtual ~CEntity();

	void SetCollider();

	template <class T>
	T* AddComponent()
	{
		CComponent* tmp = new T();
		components.push_back(tmp);
		return dynamic_cast<T*>(tmp);
	}

	// Removes the specified component.
	void RemoveComponent(CComponent* reference)
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			CComponent* component = components[i];

			if (component == reference)
			{
				components.erase(components.begin() + i);
				delete component;
				return;
			}
		}
	}
	CollisionComponent* colComponent = nullptr;
};