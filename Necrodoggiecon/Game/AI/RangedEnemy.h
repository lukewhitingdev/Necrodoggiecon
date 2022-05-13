#pragma once
#include "CAIController.h"
class RangedEnemy :
    public CAIController
{
public:
    RangedEnemy();
    virtual void Update(float deltaTime) override;

    virtual void ChasePlayer(PlayerCharacter* player) override;
    virtual void AttackPlayer(PlayerCharacter* player) override;
    virtual void GetIntoCover() override;
};

