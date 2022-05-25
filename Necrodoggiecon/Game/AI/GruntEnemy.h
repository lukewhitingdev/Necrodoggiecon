#pragma once
/*****************************************************************//**
 * \file   GruntEnemy.h
 * \brief  Header file containing all the inherited functions from CAIController and variables needed to control the Melee Enemies.
 * 
 * \author Nasser Ksous
 * \date   May 2022
 *********************************************************************/

#include "Necrodoggiecon\Game\AI\CAIController.h"
#include <Necrodoggiecon/Game/WeaponInterface.h>
#include <Necrodoggiecon/Weapons/Ranged/Crossbow.h>

/**
 * Class for the Grunt enemy. This enemy will use the weapon it is holding when it gets in range of the player.
 */
class GruntEnemy :
    public CAIController
{
public:
    GruntEnemy();

    virtual void ChasePlayer(CCharacter* player) override;
    virtual void AttackPlayer(CCharacter* player, float deltaTime) override;

private:
};

