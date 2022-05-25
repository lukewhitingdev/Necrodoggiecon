#include "EntityManager.h"
#include "Core/CEntity.h"
#include "Core/CComponent.h"
#include <algorithm>

std::vector<CEntity*> EntityManager::entities = std::vector<CEntity*>();
std::vector<CComponent*> EntityManager::uiComps = std::vector<CComponent*>();
std::vector<CComponent*> EntityManager::worldComps = std::vector<CComponent*>();
std::vector<CComponent*> EntityManager::opaqueComps = std::vector<CComponent*>();
std::vector<CComponent*> EntityManager::translucentComps = std::vector<CComponent*>();

void EntityManager::AddEntity(CEntity* entityToAdd)
{
	entities.push_back(entityToAdd);
}

void EntityManager::RemoveEntity(const CEntity* entityToRemove)
{
	auto iterator = std::find(entities.begin(), entities.end(), entityToRemove);

	if (iterator != entities.end())
		entities.erase(iterator);
	else
		Debug::LogError("Tried to remove an entity that doesnt exist.");
}

void EntityManager::AddComponent(CComponent* compToAdd)
{
	if(compToAdd->GetUseTranslucency())
		translucentComps.push_back(compToAdd);
	else
		opaqueComps.push_back(compToAdd);

	if(compToAdd->GetIsUI())
		uiComps.push_back(compToAdd);
	else
		worldComps.push_back(compToAdd);
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
		auto iterator = std::find(opaqueComps.begin(), opaqueComps.end(), compToRemove);

		if (iterator != opaqueComps.end())
			opaqueComps.erase(iterator);
		else
			Debug::LogError("Tried to remove an opaque component that doesnt exist.");
	}

	if (compToRemove->GetIsUI())
	{
		auto iterator = std::find(uiComps.begin(), uiComps.end(), compToRemove);

		if (iterator != uiComps.end())
			uiComps.erase(iterator);
		else
			Debug::LogError("Tried to remove a ui component that doesnt exist.");
	}
	else
	{
		auto iterator = std::find(worldComps.begin(), worldComps.end(), compToRemove);

		if (iterator != worldComps.end())
			worldComps.erase(iterator);
		else
			Debug::LogError("Tried to remove a world component that doesnt exist.");
	}
}

void EntityManager::SortTranslucentComponents()
{
	std::sort(translucentComps.begin(), translucentComps.end(), [](CComponent* a, CComponent* b) -> bool
		{
			return a->GetWorldPosition().z > b->GetWorldPosition().z;
		});
}
