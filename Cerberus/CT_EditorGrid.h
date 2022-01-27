#pragma once
#include "CEntity.h"
#include "CWorld_Edit.h"
class CT_EditorGrid :
    public CEntity
{
public:

    CT_EditorGrid();

    virtual void Update(float deltaTime) override;

    void SetupGrid();


  
 

  

protected: 
    class CSpriteComponent* GridSprite = nullptr;
    


};

