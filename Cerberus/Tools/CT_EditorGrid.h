#pragma once
#include "Cerberus\Core\CEntity.h"
#include "Cerberus\Core\Environment/CWorld_Edit.h"
#include "Cerberus/Core/Components/CCameraComponent.h"

class CT_EditorGrid :
    public CEntity
{
public:

    CT_EditorGrid();

    virtual void Update(float deltaTime) override;

    void SetupGrid(CCameraComponent* cam);


  
 

  

protected: 
    class CSpriteComponent* gridSprite = nullptr;
    


};

