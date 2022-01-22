#pragma once
#include "CEntity.h"
class CGridCursor :
    public CEntity
{
public:
    CGridCursor();

    class CSpriteComponent* ActiveCellSprite = nullptr;

    virtual void Update(float deltaTime) override;


    Vector3 Offset;
    Vector3 Offset_Start;
    Vector3 Offset_End;


    bool screenMoved;



    // Grid Space coordinates
    int X, Y;



    Vector2 ScreenToWorld(Vector2 Pos);

};

