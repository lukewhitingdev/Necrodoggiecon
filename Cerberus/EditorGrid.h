#pragma once
#include "CEntity.h"
#include "CWorld_Edit.h"
class EditorGrid :
    public CEntity
{
public:

    EditorGrid();

    virtual void Update(float deltaTime) override;

    void SetupGrid();

protected: 
    class CSpriteComponent* GridSprite = nullptr;
    class CSpriteComponent* ActiveCellSprite = nullptr;


};

