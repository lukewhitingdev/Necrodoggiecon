#pragma once
#include "Cerberus\Core\AI\CAIController.h"

class AlarmEnemy :
    public CAIController
{
public:
    AlarmEnemy();

    virtual void Update(float deltaTime) override;
    virtual void ChasePlayer(CCharacter* player) override;
    virtual void ChaseEnter() override;

private:
    float alarmTimer = 10.0f;
    bool onCooldown = false;

    CAudioEmitterComponent* loadNoise;
};

