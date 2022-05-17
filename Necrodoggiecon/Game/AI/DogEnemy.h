#pragma once
#include "C:\Users\k013044i\Documents\GitHub\Necrodoggiecon\Cerberus\Core\AI\CAIController.h"
class DogEnemy :
    public CAIController
{
public:
    DogEnemy();

    virtual void ChasePlayer(CCharacter* player) override;
    virtual void AttackPlayer(CCharacter* player) override;

private:
    bool onCooldown = false;
    float attackCooldown = 0.05f;
    float attackRange = 300.0f;
};

