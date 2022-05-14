/*****************************************************************//**
 * \file   CEntity.h
 * \brief  Fundamental class of the engine with a world transform and ability to have components.
 * 
 * \author Arrien Bidmead
 * \date   January 2022
 *********************************************************************/

#pragma once

#include "Cerberus\Core\CComponent.h"
#include "Cerberus/Core/Utility/CollisionManager/CollisionComponent.h"
#include "Cerberus\Core\Utility\Vector3.h"

/**
 * Fundamental class of the engine with a world transform and ability to have components.
 * Use for all gameplay things in the world.
 */
class CEntity : public CTransform
{

public:
	bool shouldUpdate = true;
	bool shouldMove = false;
	bool visible = true;

	std::vector<CComponent*> components;
	
	/**
	 * Updated automatically every single frame.
	 */
	virtual void Update(float deltaTime) = 0;
	virtual ~CEntity();

	template <class T>
	T* AddComponent()
	{
		CComponent* tmp = new T();
		tmp->SetParent(this);
		components.push_back(tmp);
		EntityManager::AddComponent(tmp);
		return dynamic_cast<T*>(tmp);
	}

	/**
	 * Removes the specified component.
	 */
	void RemoveComponent(CComponent* reference);

	CollisionComponent* colComponent = nullptr;
	virtual void HasCollided(CollisionComponent* collidedObject) {
		colComponent->Resolve(collidedObject);
		this->SetPosition(colComponent->GetPosition());
	};
};