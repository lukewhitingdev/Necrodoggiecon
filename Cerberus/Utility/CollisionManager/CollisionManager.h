#pragma once
#include "../../Engine.h"
#include "../../CEntity.h"
#include "Utility/DebugOutput/Debug.h"
#include "../../CSpriteComponent.h"
#include "Utility/CollisionManager/Components/Bodies/CollisionComponent.h"
#include <stdio.h>

struct CollisionManager
{
	static void Initialise();

	static bool CollisionDetection(CollisionComponent* base, CollisionComponent* target);

	
};

