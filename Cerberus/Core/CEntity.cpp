#include "CEntity.h"

CEntity::~CEntity()
{
	for (auto& e : components)
		delete e;
}

void CEntity::RemoveComponent(CComponent* reference)
{
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
}
