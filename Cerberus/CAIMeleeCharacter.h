#pragma once
#include "CAIController.h"
class CAIMeleeCharacter :
    public CAIController
{
    virtual void GetIntoCover(testCharacter* player) override;
};

