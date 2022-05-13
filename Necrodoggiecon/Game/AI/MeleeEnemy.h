#pragma once
#include "CAIController.h"
class MeleeEnemy :
    public CAIController
{
public:
    MeleeEnemy();
    virtual void Update(float deltaTime) override;
};

