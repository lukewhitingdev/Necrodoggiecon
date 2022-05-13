#pragma once
#include "Cerberus\Core\CEntity.h"
#include "Cerberus\Core\Environment/CWorld_Edit.h"

class CT_EditorGrid :
    public CEntity
{
public:
    CT_EditorGrid();

    virtual void Update(float deltaTime) override;

    void SetupGrid();


    ~CT_EditorGrid();

    class CGridCursor* cursorEntity;
 

  
    void SetupGrid(class CCameraComponent* cam);

protected: 
    class CSpriteComponent* gridSprite = nullptr;

};

