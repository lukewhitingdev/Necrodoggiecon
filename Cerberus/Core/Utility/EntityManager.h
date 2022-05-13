#pragma once
#include "Core/Engine.h"
#include <unordered_map>

class EntityManager
{
	static std::unordered_map<uintptr_t, class CEntity*> entities;

	static std::unordered_map<uintptr_t, class CComponent*> opaqueComps;
	static std::vector<class CComponent*> translucentComps;

public:
	static void AddEntity(class CEntity* entityToAdd);
	static void RemoveEntity(const class CEntity* entityToRemove);

	static void AddComponent(class CComponent* compToAdd);
	static void RemoveComponent(const class CComponent* compToRemove);

	static void SortTranslucentComponents();

	static const std::unordered_map<uintptr_t, class CEntity*>* GetEntitiesMap();
	static const std::unordered_map<uintptr_t, class CComponent*>* GetOpaqueCompsMap();
	static const std::vector<class CComponent*>* GetTranslucentCompsVector();
};
