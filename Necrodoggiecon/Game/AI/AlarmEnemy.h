#pragma once
#include "C:\Users\k013044i\Documents\GitHub\Necrodoggiecon\Cerberus\Core\AI\CAIController.h"
class AlarmEnemy :
    public CAIController
{
public:
    AlarmEnemy();

    virtual void ChasePlayer(CCharacter* player) override;
    virtual void ChaseEnter() override;

private:
    float alarmTimer = 1.0f;

    CAudioEmitterComponent* loadNoise;
};

