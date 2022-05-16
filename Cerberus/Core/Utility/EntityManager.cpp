#include "EntityManager.h"
#include "Core/CEntity.h"
#include "Core/CComponent.h"
#include <algorithm>

std::unordered_map<uintptr_t, class CEntity*> EntityManager::entities = std::unordered_map<uintptr_t, class CEntity*>();
std::unordered_map<uintptr_t, class CComponent*> EntityManager::opaqueComps = std::unordered_map<uintptr_t, class CComponent*>();
std::vector<class CComponent*> EntityManager::translucentComps = std::vector<class CComponent*>();

void EntityManager::AddEntity(CEntity* entityToAdd)
{
	entities.emplace(std::make_pair((uintptr_t)entityToAdd, entityToAdd));
}

void EntityManager::RemoveEntity(const CEntity* entityToRemove)
{
	if (entities.find((uintptr_t)entityToRemove) != entities.end())
		entities.erase((uintptr_t)entityToRemove);
	else
		Debug::LogError("Tried to remove an entity that doesnt exist.");
}

void EntityManager::AddComponent(CComponent* compToAdd)
{
	if(compToAdd->GetUseTranslucency())
		translucentComps.push_back(compToAdd);
	else
		opaqueComps.emplace(std::make_pair((uintptr_t)compToAdd, compToAdd));
}

void EntityManager::RemoveComponent(const CComponent* compToRemove)
{
	if (compToRemove->GetUseTranslucency())
	{
		auto iterator = std::find(translucentComps.begin(), translucentComps.end(), compToRemove);

		if (iterator != translucentComps.end())
			translucentComps.erase(iterator);
		else
			Debug::LogError("Tried to remove an translucent component that doesnt exist.");
	}
	else
	{
		if (opaqueComps.find((uintptr_t)compToRemove) != opaqueComps.end())
			opaqueComps.erase((uintptr_t)compToRemove);
		else
			Debug::LogError("Tried to remove an opaque component that doesnt exist.");
	}
}

void EntityManager::SortTranslucentComponents()
{
	std::sort(translucentComps.begin(), translucentComps.end(), [](CComponent* a, CComponent* b) -> bool
		{
			return a->GetWorldPosition().z > b->GetWorldPosition().z;
		});
}

const std::unordered_map<uintptr_t, class CEntity*>* EntityManager::GetEntitiesMap()
{
	return &entities;
}

const std::unordered_map<uintptr_t, class CComponent*>* EntityManager::GetOpaqueCompsMap()
{
	return &opaqueComps;
}

const std::vector<class CComponent*>* EntityManager::GetTranslucentCompsVector()
{
	return &translucentComps;
}
