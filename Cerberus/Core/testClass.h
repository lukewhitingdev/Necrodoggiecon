#pragma once
#include "../Engine.h"
#include "../CEntity.h"
#include <stdio.h>

class TestClass : public CEntity
{
	class CSpriteComponent* sprite = nullptr;
	bool rotDir = 0;
	float timeElapsed = 0;
public:
	TestClass();
	virtual void Update(float deltaTime) override;
	virtual ~TestClass();
};

