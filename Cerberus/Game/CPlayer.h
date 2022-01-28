#pragma once
#include "Engine.h"
#include "CEntity.h"
#include <stdio.h>


class CPlayer : public CEntity
{
    class CSpriteComponent* sprite = nullptr;
    float timeElapsed = 0;
public:
    CPlayer();
    virtual void Update(float deltaTime) override;
    virtual ~CPlayer();
};

