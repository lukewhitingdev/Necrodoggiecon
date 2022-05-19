#pragma once
#include "Cerberus\Core\AI\CAIController.h"
class DogEnemy :
    public CAIController
{
public:
    DogEnemy();

    virtual void Update(float deltaTime) override;
    virtual void ChasePlayer(CCharacter* player) override;
    virtual void AttackEnter(CCharacter* player) override;
    virtual void AttackPlayer(CCharacter* player) override;

private:
    bool onCooldown = false;
    float attackCooldown = 0.0f;
    float attackTimer = 0.5f;
    float attackRange = 300.0f;
    Vector3 targetPosition;
};

