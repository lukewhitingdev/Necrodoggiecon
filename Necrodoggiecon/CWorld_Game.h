#pragma once
#include "Cerberus\Core\Environment\CWorld.h"
class CWorld_Game :
    public CWorld
{



public:

    CWorld_Game(int Slot);

    virtual void SetupWorld();

    virtual void UnloadWorld();

    virtual void LoadEntities(int Slot);
};

