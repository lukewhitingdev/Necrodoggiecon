/*******************************************************************
 * \file   CT_EditorEntity.cpp
 * \brief  
 * 
 * \author Samuel Elliot Jackson
 * \date   May 2022
 *********************************************************************/
#include "CT_EditorEntity.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include "Core/Components/CSpriteComponent.h"
#include "Dependencies/NlohmannJson/json.hpp"
#include <WorldConstants.h>

using json = nlohmann::json;

/**
 * Standard initialiser.
 * 
 */
CT_EditorEntity::CT_EditorEntity()
{
	inspectType = EditorEntityType::Standard;
}

/**
 * Standard update function, inherited from CEntity.
 * 
 * \param deltaTime Time taken betweeen frames.
 */
void CT_EditorEntity::Update(float deltaTime)
{
}

/**
 * Virtual function, used to initialise the entity.
 * 
 * \param SlotID EntitySlot.
 */
void CT_EditorEntity::InitialiseEntity(int SlotID)
{


	
}
/**
 * Standard initialiser for EditorEntity_Enemy.
 * 
 */
CT_EditorEntity_Enemy::CT_EditorEntity_Enemy()
{
	sprite = AddComponent<CSpriteComponent>(NAME_OF(sprite));
	inspectType = EditorEntityType::Enemy;
	int itemIndex = 0;



}

CT_EditorEntity_Enemy::~CT_EditorEntity_Enemy()
{
	
}

/**
 * Assign weapon to the Entity.
 * 
 * \param WeaponID Weapon Name
 * \param Index Weapon Index
 */
void CT_EditorEntity_Enemy::AssignWeapon(char* WeaponID, int Index)
{
	 current_item = WeaponID; 
	 itemIndex = Index; 

	 Debug::Log("WeaponAssigned: %c | %d", WeaponID, Index);
}

std::vector<class CT_EditorEntity_Waypoint*> CT_EditorEntity_Enemy::GetWaypointList()
{
	std::vector<CT_EditorEntity_Waypoint*> ReturnList;
	for (int i = 0; i < Waypoints.size(); i++)
	{
		if (Waypoints[i] != nullptr)
		{
			ReturnList.push_back(Waypoints[i]);
		}
	}
	return ReturnList;
}


/**
 * Standard update function, inherited from CEntity.
 *
 * \param deltaTime Time taken betweeen frames.
 */
void CT_EditorEntity_Enemy::Update(float deltaTime)
{
}
/**
 * Initialises Enemy Entity.
 * 
 * \param SlotID Determines AI Type
 */
void CT_EditorEntity_Enemy::InitialiseEntity(int SlotID)
{
	entitySlotID = SlotID;
	switch (SlotID)
	{
	case 0:
		sprite->LoadTexture("Resources\\EditorEntities\\EnemyCharacters\\MageEnemy.dds");
		sprite->SetRenderRect(XMUINT2(64, 64));
		sprite->SetSpriteSize(XMUINT2(64, 64));
		break;
	case 1:
		sprite->LoadTexture("Resources\\EditorEntities\\EnemyCharacters\\MeleeEnemy.dds");
		sprite->SetRenderRect(XMUINT2(64, 64));
		sprite->SetSpriteSize(XMUINT2(64, 64));
	case 2: 
		sprite->LoadTexture("Resources\\EditorEntities\\EnemyCharacters\\MeleeEnemy.dds");
		sprite->SetRenderRect(XMUINT2(64, 64));
		sprite->SetSpriteSize(XMUINT2(64, 64));
		break;
	}
}

/**
 * Toggles whether Waypoints should be rendered to the screen or not.
 * 
 * \param Display
 */
void CT_EditorEntity_Enemy::ToggleWaypoints(bool Display)
{

	if (Display)
	{
		for (int i = 0; i < Waypoints.size(); i++)
		{
			Vector3 Pos = Waypoints[i]->GetPosition();
			Waypoints[i]->SetPosition(Pos.x, Pos.y, 50);
		}
	}
	else
	{
		for (int i = 0; i < Waypoints.size(); i++)
		{
			Vector3 Pos = Waypoints[i]->GetPosition();
			Waypoints[i]->SetPosition(Pos.x, Pos.y, -1);
		}
	}
	
}
/**
 * Adds a waypoint to the Enemy Entity.
 * 
 * \param Position Waypoint Position
 * \return returns the Waypoint Entity
 */
CT_EditorEntity_Waypoint* CT_EditorEntity_Enemy::AddWaypoint(Vector2 Position)
{
	
	Vector3 Pos = Vector3(Position.x, Position.y, 0) * (tileScale * tileScaleMultiplier);
	Pos.z = -1;
	CT_EditorEntity_Waypoint* TempWaypoint = Engine::CreateEntity<CT_EditorEntity_Waypoint>();
	TempWaypoint->SetPosition(Pos);
	TempWaypoint->gridPos = Position;
	TempWaypoint->waypointOrder = Waypoints.size();
	Waypoints.push_back(TempWaypoint);
	return TempWaypoint;
}

/**
 * Removes the waypoint from the enemy entity.
 * 
 * \param Index Index of the waypoint.
 */
void CT_EditorEntity_Enemy::RemoveWaypoint(int Index)
{
	std::vector<CT_EditorEntity_Waypoint*> TempList;
	for (int i = 0; i < Waypoints.size(); i++)
	{
		if (i != Index) TempList.push_back(Waypoints[i]);
		else
		{
			Engine::DestroyEntity(Waypoints[i]);
		}
	}
	Waypoints.clear();
	Waypoints = TempList;
}

/**
 * Standard constructor for EditorEntity_Waypoint.
 * 
 */
CT_EditorEntity_Waypoint::CT_EditorEntity_Waypoint()
{
	inspectType = EditorEntityType::Waypoint;
	sprite = AddComponent<CSpriteComponent>(NAME_OF(sprite));
	sprite->LoadTexture("Resources\\EditorEntities\\WaypointIcon.dds");
	sprite->SetRenderRect(XMUINT2(32, 32));
	sprite->SetSpriteSize(XMUINT2(32, 32));
	
}

/**
 * Standard update function, inherited from CEntity.
 *
 * \param deltaTime Time taken betweeen frames.
 */
void CT_EditorEntity_Waypoint::Update(float deltaTime)
{
}

/**
 * Initialises Entity, unused as only 1 type of waypoint.
 * 
 * \param SlotID
 */
void CT_EditorEntity_Waypoint::InitialiseEntity(int SlotID)
{

}

/**
 * Initialises the Player start entity.
 * 
 */
CT_EditorEntity_PlayerStart::CT_EditorEntity_PlayerStart()
{
	inspectType = EditorEntityType::Flag;
	sprite = AddComponent<CSpriteComponent>(NAME_OF(sprite));
	sprite->LoadTexture("Resources\\EditorEntities\\Flag.dds");
	sprite->SetRenderRect(XMUINT2(32, 32));
	sprite->SetSpriteSize(XMUINT2(64, 64));
	SetPosition(Vector3(320, 320, -1));
}
/**
 * Standard update function, inherited from CEntity.
 *
 * \param deltaTime Time taken betweeen frames.
 */
void CT_EditorEntity_PlayerStart::Update(float deltaTime)
{
}

/**
 * Standard initialiser for the EditorEntity_WeaponHolder.
 * 
 */
CT_EditorEntity_WeaponHolder::CT_EditorEntity_WeaponHolder()
{
	sprite = AddComponent<CSpriteComponent>(NAME_OF(spriteComponentLegs));

	sprite->LoadTexture("Resources\\EditorEntities\\WaypointIcon.dds");
	sprite->SetRenderRect(XMUINT2(32, 32));
	sprite->SetSpriteSize(XMUINT2(64, 64));
	
	//weaponSprite = AddComponent<CSpriteComponent>();
//	weaponSprite->LoadTexture("Resources\\EditorEntities\\Flag.dds");
//	weaponSprite->SetRenderRect(XMUINT2(32, 32));
	//weaponSprite->SetSpriteSize(XMUINT2(64, 64));
	inspectType = EditorEntityType::WeaponHolder;
	int itemSlot = 0;
}

/**
 * Assigns A weapon to the Holder.
 * 
 * \param WeaponID The weapon name
 * \param Index The Weapon Index
 */
void CT_EditorEntity_WeaponHolder::AssignWeapon(char* WeaponID, int Index)
{
	current_item = WeaponID;
	itemSlot = Index;

	Debug::Log("WeaponAssigned: %c | %d", WeaponID, Index);


}

/**
 * Standard update function, inherited from CEntity.
 *
 * \param deltaTime Time taken betweeen frames.
 */
void CT_EditorEntity_WeaponHolder::Update(float deltaTime)
{
}

/**
 * Initialises the weapon holder.
 * 
 * \param SlotID
 */
void CT_EditorEntity_WeaponHolder::InitialiseEntity(int SlotID)
{
	//ToDo: Update sprite with the assigned weapon
}
