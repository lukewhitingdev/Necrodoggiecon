/*****************************************************************//**
 * \file   DogEnemy.h
 * \brief  Header for the dog enemy type.
 * 
 * \author Nasser Ksous
 * \date   May 2022
 *********************************************************************/
#pragma once
#include "Necrodoggiecon\Game\AI\CAIController.h"

/**
 * Class for the dog enemy. The dog will dash at the player once it's within attack range.
 */
class DogEnemy :
    public CAIController
{
public:
    DogEnemy();

    virtual void Update(float deltaTime) override;
    virtual void ChasePlayer(CCharacter* player) override;
    virtual void AttackEnter(CCharacter* player) override;
    virtual void AttackPlayer(CCharacter* player, float deltaTime) override;

private:
    bool onCooldown = false;
    float attackCooldown = 0.0f;
    float attackTimer = 1.0f;
    float attackRange = 300.0f;
    const float walkAnimationSpeed = 1.3f;
    Vector3 targetPosition;
};

