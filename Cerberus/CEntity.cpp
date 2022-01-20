#include "CEntity.h"

CEntity::~CEntity()
{
	for (auto& e : components)
		delete e;
};

