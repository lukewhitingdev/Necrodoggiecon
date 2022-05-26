/*****************************************************************//**
 * \file   AlarmEnemy.h
 * \brief  Header file for the alarm enemy.
 * 
 * \author Nasser Ksous
 * \date   May 2022
 *********************************************************************/
#pragma once
#include "Necrodoggiecon\Game\AI\CAIController.h"

/**
 * Class for the alarm enemy. It will ring a bell once it sees the player.
 */
class AlarmEnemy :
    public CAIController
{
public:
    AlarmEnemy();

    virtual void Update(float deltaTime) override;
    virtual void ChasePlayer(CCharacter* player) override;

private:
    float alarmTimer = 10.0f;
    bool onCooldown = false;

    CAudioEmitterComponent* loadNoise;
};

