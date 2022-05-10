#pragma once
#include "Cerberus\Core\CEntity.h"
#include "Cerberus/Core/Components/CCameraComponent.h"
class CGridCursor :
    public CEntity
{
public:
    CGridCursor();

    class CSpriteComponent* activeCellSprite = nullptr;

    void SetCamera(CCameraComponent* cam);

    virtual void Update(float deltaTime) override;

    void UpdateSize(int X, int Y);

    Vector3 Offset;
    Vector3 Offset_Start;
    Vector3 Offset_End;

    bool screenMoved;
    bool cellSelected;
    Vector3 selectedCell_1;
    bool wasMouseReleased;

    CCameraComponent* camera;

};

