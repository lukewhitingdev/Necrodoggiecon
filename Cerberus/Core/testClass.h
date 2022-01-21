#pragma once
#include "../Engine.h"
#include "../CEntity.h"
#include <stdio.h>
#include "Utility/CollisionManager/Components/Bodies/CollisionComponent.h"

class TestClass : public CEntity
{
	class CSpriteComponent* sprite = nullptr;

	float timeElapsed = 0;
public:
	TestClass();
	virtual void Update(float deltaTime) override;
	virtual ~TestClass();
};

