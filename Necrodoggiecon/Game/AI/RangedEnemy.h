#pragma once
/*****************************************************************//**
 * \file   RangedEnemy.h
 * \brief  Header file containing all the inherited functions from CAIController and variables needed to control the Ranged Enemies.
 * 
 * \author Nasser Ksous
 * \date   May 2022
 *********************************************************************/

#include "Cerberus/Core/AI/CAIController.h"
class RangedEnemy :
    public CAIController
{
public:
    RangedEnemy();
    virtual void Update(float deltaTime) override;

    virtual void ChasePlayer(CCharacter* player) override;
    virtual void AttackPlayer(CCharacter* player) override;
    virtual void GetIntoCover() override;

private:
    std::vector<PlayerController*> playersController = Engine::GetEntityOfType<PlayerController>();
};

