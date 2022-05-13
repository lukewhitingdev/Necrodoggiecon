#pragma once
#include "CAIController.h"
class MeleeEnemy :
    public CAIController
{
public:
    MeleeEnemy();
    virtual void Update(float deltaTime) override;

    virtual void ChasePlayer(PlayerCharacter* player) override;
    virtual void AttackPlayer(PlayerCharacter* player) override;
    virtual void GetIntoCover() override;
};

