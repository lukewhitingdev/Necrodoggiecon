#include "Cerberus\Core\CEntity.h"

CEntity::~CEntity()
{
	for (auto& e : components)
	{
		EntityManager::RemoveComponent(e);

		delete e;
	}
}

void CEntity::RemoveComponent(CComponent* reference)
{
	EntityManager::RemoveComponent(reference);

	auto iterator = std::find(components.begin(), components.end(), reference);

	if (iterator != components.end())
	{
		components.erase(iterator);
		delete reference;
	}
	else
	{
		Debug::LogError("Tried to remove an translucent component that doesnt exist.");
	}
}
