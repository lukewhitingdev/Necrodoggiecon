#pragma once
#include "CEntity.h"
class CGridCursor :
    public CEntity
{
public:
    CGridCursor();

    class CSpriteComponent* ActiveCellSprite = nullptr;

    virtual void Update(float deltaTime) override;






};

