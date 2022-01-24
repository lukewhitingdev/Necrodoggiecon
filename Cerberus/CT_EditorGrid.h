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


    void SetCursorPosition(Vector2 Position);
    void UpdateHighlightScale();

    void ActivateCursorScale();
    void ClearCursorScale();

    bool isCursorScaling;

protected: 
    class CSpriteComponent* GridSprite = nullptr;
    class CSpriteComponent* ActiveCellSprite = nullptr;


};

