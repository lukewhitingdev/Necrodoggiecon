#pragma once
/*****************************************************************//**
 * \file   MeleeEnemy.h
 * \brief  Header file containing all the inherited functions from CAIController and variables needed to control the Melee Enemies.
 * 
 * \author k013044i
 * \date   May 2022
 *********************************************************************/

#include "Cerberus/Core/AI/CAIController.h"
#include "Necrodoggiecon/Game/weapons.h"

class MeleeEnemy :
    public CAIController
{
public:
    MeleeEnemy();

    virtual void ChasePlayer(CCharacter* player) override;
    virtual void AttackPlayer(CCharacter* player) override;

private:
    std::vector<PlayerController*> playersController = Engine::GetEntityOfType<PlayerController>();
    Weapon* weapon = nullptr;
};

