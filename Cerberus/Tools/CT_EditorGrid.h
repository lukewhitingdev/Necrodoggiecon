#pragma once
#include "CEntity.h"
#include "Environment/CWorld_Edit.h"

class CT_EditorGrid :
    public CEntity
{
public:

    CT_EditorGrid();

    virtual void Update(float deltaTime) override;

    void SetupGrid();


    ~CT_EditorGrid();

    class CGridCursor* cursorEntity;
 

  

protected: 
    class CSpriteComponent* gridSprite = nullptr;
    


};

