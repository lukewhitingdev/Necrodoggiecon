#pragma once
/*****************************************************************//**
 * \file   GruntEnemy.h
 * \brief  Header file containing all the inherited functions from CAIController and variables needed to control the Melee Enemies.
 * 
 * \author Nasser Ksous
 * \date   May 2022
 *********************************************************************/

#include "Cerberus/Core/AI/CAIController.h"
#include "Necrodoggiecon/Game/weapons.h"
#include <Necrodoggiecon/Game/WeaponInterface.h>

/**
 * Class for the Grunt enemy. This enemy will use the weapon it is holding when it gets in range of the player.
 */
class GruntEnemy :
    public CAIController
{
public:
    GruntEnemy();

    virtual void ChasePlayer(PlayerCharacter* player) override;
    virtual void AttackPlayer(PlayerCharacter* player, float deltaTime) override;

private:
    std::vector<PlayerController*> playersController = Engine::GetEntityOfType<PlayerController>();
    WeaponInterface* weapon = nullptr;
};

