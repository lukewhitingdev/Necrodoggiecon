#pragma once
#include "CEntity.h"
class CGridCursor :
    public CEntity
{
public:
    CGridCursor();

    class CSpriteComponent* ActiveCellSprite = nullptr;

    virtual void Update(float deltaTime) override;

    void UpdateSize(int X, int Y);

    Vector3 Offset;
    Vector3 Offset_Start;
    Vector3 Offset_End;


    bool screenMoved;



    // Grid Space coordinates
    int CachedX, CachedY;



    bool cellSelected;

    Vector3 selectedCell_1;
    Vector3 selectedCell_2;



    Vector2 ScreenToWorld(Vector2 Pos);



    bool wasMouseReleased;

};

