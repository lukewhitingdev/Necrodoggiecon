#pragma once
#include "Cerberus\Core\CEntity.h"

enum class EditorEntityType
{
    None, Standard, Enemy, Interactable, Waypoint, Flag
};
class CT_EditorEntity :
    public CEntity
{
protected:

   // class CSpriteComponent* sprite = nullptr;

    int entitySlotID;


    EditorEntityType inspectType;

public:

    class CSpriteComponent* sprite = nullptr;

    CT_EditorEntity();

    virtual void Update(float deltaTime) override;


    virtual void InitialiseEntity(int SlotID);

    virtual void SaveEntity(int Index, int MapSlot);

    EditorEntityType GetType() { return inspectType; }

    int GetSlot() { return entitySlotID; }



};

class CT_Editor_ItemHolder :
    public CT_EditorEntity
{
protected:

    // class CSpriteComponent* sprite = nullptr;

 

    int itemSlot;
public:



    CT_Editor_ItemHolder();

    virtual void Update(float deltaTime) override;


  

    virtual void InitialiseEntity(int SlotID);



};



class CT_EditorEntity_Waypoint :
    public CT_EditorEntity
{
protected:

    // class CSpriteComponent* sprite = nullptr;





public:

    Vector2 GetGridPos();

    CT_EditorEntity_Waypoint();


    int waypointOrder;
    Vector2 gridPos;

    virtual void Update(float deltaTime) override;




    virtual void InitialiseEntity(int SlotID);



};


class CT_EditorEntity_Enemy :
    public CT_EditorEntity
{
protected:

    // class CSpriteComponent* sprite = nullptr;

    bool displayWaypoints = false;

public:
    
   

    std::vector<CT_EditorEntity_Waypoint*> Waypoints;


    CT_EditorEntity_Enemy();

    virtual void Update(float deltaTime) override;


    virtual void InitialiseEntity(int SlotID);

    virtual void SaveEntity(int Index, int MapSlot);

    void ToggleWaypoints(bool Display);

    CT_EditorEntity_Waypoint* AddWaypoint(Vector2 Position);

    void RemoveWaypoint(int Index);
    
   
    





};

class CT_EditorEntity_PlayerStart :
    public CT_EditorEntity
{
public:

    CT_EditorEntity_PlayerStart();

    virtual void Update(float deltaTime) override;






};


