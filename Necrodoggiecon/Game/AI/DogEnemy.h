/*****************************************************************//**
 * \file   DogEnemy.h
 * \brief  Header for the dog enemy type.
 * 
 * \author Nasser Ksous
 * \date   May 2022
 *********************************************************************/
#pragma once
#include "Cerberus\Core\AI\CAIController.h"

/**
 * Class for the dog enemy. The dog will dash at the player once it's within attack range.
 */
class DogEnemy :
    public CAIController
{
public:
    DogEnemy();

    virtual void Update(float deltaTime) override;
    virtual void ChasePlayer(PlayerCharacter* player) override;
    virtual void AttackEnter(PlayerCharacter* player) override;
    virtual void AttackPlayer(PlayerCharacter* player) override;

private:
    bool onCooldown = false;
    float attackCooldown = 0.0f;
    float attackTimer = 1.0f;
    float attackRange = 300.0f;
    Vector3 targetPosition;
};

