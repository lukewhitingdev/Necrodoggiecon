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
	bool shouldUpdate = true;
	bool shouldMove = false;
	bool visible = true;

	std::vector<CComponent*> components;

public:
	/**
	 * Sets if this entity will be automatically updated via the Update().
	 */
	void SetShouldUpdate(const bool& newShouldUpdate) { shouldUpdate = newShouldUpdate; }

	/**
	 * Sets whether this entity will move for collision detection.
	 */
	void SetShouldMove(const bool& newShouldMove) { shouldMove = newShouldMove; }

	/**
	 * Sets if this entity and all it's components will be rendered.
	 */
	void SetVisible(const bool& newVisibility) { visible = newVisibility; }

	const bool& GetShouldUpdate() const { return shouldUpdate; }
	const bool& GetShouldMove() const { return shouldMove; }
	const bool& GetVisible() const { return visible; }
	const std::vector<CComponent*>& GetAllComponents() const { return components; }

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

	template<class T>
	T* GetComponentOfType()
	{
		T* comp = nullptr;
		for(auto& component : components)
		{
			comp = dynamic_cast<T*>(component);
			if(comp != nullptr)
			{
				return comp;
			}
		}

		return nullptr;
	}

	template<class T>
	std::vector<T*> GetAllComponentsOfType()
	{
		std::vector<T*> output;
		T* comp = nullptr;
		for (auto& component : components)
		{
			comp = dynamic_cast<T*>(component);
			if (comp != nullptr)
			{
				output.push_back(comp);
			}
		}

		return output;
	}

	/**
	 * Removes the specified component.
	 */
	void RemoveComponent(CComponent* reference);

	CollisionComponent* colComponent = nullptr;
	virtual void HasCollided(CollisionComponent* collidedObject) 
	{
		if (!collidedObject->GetTrigger())
		{
			colComponent->Resolve(collidedObject);
			this->SetPosition(colComponent->GetPosition());
		}
	};
};