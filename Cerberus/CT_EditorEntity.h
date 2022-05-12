#pragma once
#include "CEntity.h"

enum class EditorEntityType
{
    None, Standard, Enemy, Interactable, Waypoint
};
class CT_EditorEntity :
    public CEntity
{
protected:

   // class CSpriteComponent* sprite = nullptr;

    int EntitySlotID;


    EditorEntityType InspectType;

public:

    class CSpriteComponent* sprite = nullptr;

    CT_EditorEntity();

    virtual void Update(float deltaTime) override;


    virtual void InitialiseEntity(int SlotID);

    virtual void SaveEntity(int Index, int MapSlot);

    EditorEntityType GetType() { return InspectType; }

    int GetSlot() { return EntitySlotID; }



};

class CT_Editor_ItemHolder :
    public CT_EditorEntity
{
protected:

    // class CSpriteComponent* sprite = nullptr;

 

    int ItemSlot;
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



    CT_EditorEntity_Waypoint();


    int WaypointOrder;

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

    void AddWaypoint(Vector2 Position);

    void RemoveWaypoint(int Index);
    
   
    





};


