#pragma once
#include "Cerberus\Core\CEntity.h"

enum class EditorEntityType
{
    None, Standard, Enemy, Interactable, Waypoint, Flag, WeaponHolder
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

class CT_EditorEntity_WeaponHolder :
    public CT_EditorEntity
{
protected:

    // class CSpriteComponent* sprite = nullptr;

 
    char* current_item = (char*)"Dagger";
    int itemSlot = 0;

    CSpriteComponent* weaponSprite;
public:



    CT_EditorEntity_WeaponHolder();

  
    char* GetWeaponName() { return current_item; }
    int GetAssignedWeapon() { return itemSlot; }
    void AssignWeapon(char* WeaponID, int Index);
    
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

    char* current_item = (char*)"Dagger";
    int itemIndex = 0;

public:
    
   

    std::vector<CT_EditorEntity_Waypoint*> Waypoints;

    char* GetWeaponName() { return current_item; }
    int GetAssignedWeapon() { return itemIndex; }
    void AssignWeapon(char* WeaponID, int Index);

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


