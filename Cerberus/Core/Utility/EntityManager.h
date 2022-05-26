/*****************************************************************//**
 * \file   EntityManager.h
 * \brief  Static class for tracking entities and components while accommodating translucency.
 * 
 * \author Arrien Bidmead
 * \date   May 2022
 *********************************************************************/

#pragma once
#include <unordered_map>

/**
 * Static class for tracking entities and components while accommodating translucency.
 */
class EntityManager
{
	static std::vector<class CEntity*> entities;
	static std::vector<class CEntity*> pendingEntityDeletions;

	static std::vector<class CComponent*> opaqueComps;
	static std::vector<class CComponent*> translucentComps;

public:
	/**
	 * Adds the input entity to the internal vector.
	 */
	static void AddEntity(class CEntity* entityToAdd);

	static void AddDeletedEntity(class CEntity* entityToDelete);

	static void DestroyAllPendingEntitiesDeletions();

	/**
	 * Removes the input entity to the internal vector.
	 * Note: does NOT delete the entity.
	 */
	static bool RemoveEntity(const class CEntity* entityToRemove);

	/**
	 * Adds the input component to the internal containers based on translucency boolean in CComponent.
	 */
	static void AddComponent(class CComponent* compToAdd);

	/**
	 * Removes the input component to the internal containers based on translucency boolean in CComponent.
	 * Note: does NOT delete the component.
	 */
	static bool RemoveComponent(const class CComponent* compToRemove);

	/**
	 * Sorts the translucent components container ready for drawing.
	 * This is done automatically in the engine's draw function so DON'T call this.
	 */
	static void SortTranslucentComponents();

	/**
	 * Remove and delete all items from the entity manager.
	 */
	static void Purge();

	static const std::vector<class CEntity*>* GetEntitiesVector() { return &entities; };
	static const std::vector<class CComponent*>* GetOpaqueCompsVector() { return &opaqueComps; };
	static const std::vector<class CComponent*>* GetTranslucentCompsVector() { return &translucentComps; };
};
