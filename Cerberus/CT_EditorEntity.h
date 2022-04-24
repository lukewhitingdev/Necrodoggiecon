#pragma once
#include "CEntity.h"
class CT_EditorEntity :
    public CEntity
{
protected:

    class CSpriteComponent* sprite = nullptr;

    int EntitySlotID;
public:

  

    CT_EditorEntity();

    virtual void Update(float deltaTime) override;


    void InitialiseEntity(int SlotID);





};

