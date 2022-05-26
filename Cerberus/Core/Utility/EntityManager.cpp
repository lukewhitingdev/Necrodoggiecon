#include "EntityManager.h"
#include "Core/CEntity.h"
#include "Core/CComponent.h"
#include <algorithm>

std::vector<CEntity*> EntityManager::entities = std::vector<CEntity*>();
std::vector<CEntity*> EntityManager::pendingEntityDeletions = std::vector<CEntity*>();
std::vector<CComponent*> EntityManager::opaqueComps = std::vector<CComponent*>();
std::vector<CComponent*> EntityManager::translucentComps = std::vector<CComponent*>();

void EntityManager::AddEntity(CEntity* entityToAdd)
{
	entities.push_back(entityToAdd);
}

void EntityManager::AddDeletedEntity(CEntity* entityToDelete)
{
	pendingEntityDeletions.push_back(entityToDelete);
}

void EntityManager::DestroyAllPendingEntitiesDeletions()
{
	while (pendingEntityDeletions.size() > 0)
	{
		CEntity* e = pendingEntityDeletions.back();

		if (EntityManager::RemoveEntity(e))
			delete e;

		pendingEntityDeletions.pop_back();
	}
}

bool EntityManager::RemoveEntity(const CEntity* entityToRemove)
{
	auto iterator = std::find(entities.begin(), entities.end(), entityToRemove);

	bool succeeded = iterator != entities.end();
	if (succeeded)
		entities.erase(iterator);
	else
		Debug::LogError("Tried to remove an entity that doesnt exist.");

	return succeeded;
}

void EntityManager::AddComponent(CComponent* compToAdd)
{
	if(compToAdd->GetUseTranslucency())
		translucentComps.push_back(compToAdd);
	else
		opaqueComps.push_back(compToAdd);
}

bool EntityManager::RemoveComponent(const CComponent* compToRemove)
{
	bool succeeded = false;
	if (compToRemove->GetUseTranslucency())
	{
		auto iterator = std::find(translucentComps.begin(), translucentComps.end(), compToRemove);

		succeeded |= iterator != translucentComps.end();
		if (succeeded)
			translucentComps.erase(iterator);
		else
			Debug::LogError("Tried to remove an translucent component that doesnt exist.");
	}
	else
	{
		auto iterator = std::find(opaqueComps.begin(), opaqueComps.end(), compToRemove);

		succeeded |= iterator != opaqueComps.end();
		if (succeeded)
			opaqueComps.erase(iterator);
		else
			Debug::LogError("Tried to remove an opaque component that doesnt exist.");
	}

	return succeeded;
}

void EntityManager::SortTranslucentComponents()
{
	std::sort(translucentComps.begin(), translucentComps.end(), [](CComponent* a, CComponent* b) -> bool
		{
			return a->GetWorldPosition().z > b->GetWorldPosition().z;
		});
}

void EntityManager::Purge()
{
	for (int i = 0; i < entities.size(); i++)
	{
		CEntity* e = entities.at(i);

		EntityManager::AddDeletedEntity(e);
	}
}
