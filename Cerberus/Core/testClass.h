#pragma once
#include "../Engine.h"
#include "../CEntity.h"
#include "../CMeshComponent.h"
#include <stdio.h>

class TestClass : public CEntity
{
	CMeshComponent* mesh = nullptr;
public:
	TestClass();
	virtual void Update(float deltaTime) override;
	virtual ~TestClass();
};

