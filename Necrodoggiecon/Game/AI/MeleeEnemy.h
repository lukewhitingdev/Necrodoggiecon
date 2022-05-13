#pragma once
/*****************************************************************//**
 * \file   MeleeEnemy.h
 * \brief  Header file containing all the inherited functions from CAIController and variables needed to control the Melee Enemies.
 * 
 * \author k013044i
 * \date   May 2022
 *********************************************************************/

#include "Cerberus/Core/AI/CAIController.h"
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

