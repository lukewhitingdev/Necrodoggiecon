#include "CT_EditorEntity.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include "Core/Components/CSpriteComponent.h"
#include "Dependencies/NlohmannJson/json.hpp"
#include <WorldConstants.h>

using json = nlohmann::json;


CT_EditorEntity::CT_EditorEntity()
{
	inspectType = EditorEntityType::Standard;
}

void CT_EditorEntity::Update(float deltaTime)
{
}

void CT_EditorEntity::InitialiseEntity(int SlotID)
{


	
}

void CT_EditorEntity::SaveEntity(int Index, int MapSlot)
{
}

void CT_EditorEntity_Enemy::AssignWeapon(char* WeaponID, int Index)
{
	 current_item = WeaponID; 
	 itemIndex = Index; 

	 Debug::Log("WeaponAssigned: %c | %d", WeaponID, Index);
}

CT_EditorEntity_Enemy::CT_EditorEntity_Enemy()
{
	sprite = AddComponent<CSpriteComponent>(NAME_OF(sprite));
	inspectType = EditorEntityType::Enemy;
	int itemIndex = 0;



}

void CT_EditorEntity_Enemy::Update(float deltaTime)
{
}

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
		break;
	}
}

void CT_EditorEntity_Enemy::SaveEntity(int Index, int MapSlot)
{
	
	
	
	
	


}

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

CT_EditorEntity_Waypoint::CT_EditorEntity_Waypoint()
{
	inspectType = EditorEntityType::Waypoint;
	sprite = AddComponent<CSpriteComponent>(NAME_OF(sprite));
	sprite->LoadTexture("Resources\\EditorEntities\\WaypointIcon.dds");
	sprite->SetRenderRect(XMUINT2(32, 32));
	sprite->SetSpriteSize(XMUINT2(32, 32));
	
}

void CT_EditorEntity_Waypoint::Update(float deltaTime)
{
}

void CT_EditorEntity_Waypoint::InitialiseEntity(int SlotID)
{

}

CT_EditorEntity_PlayerStart::CT_EditorEntity_PlayerStart()
{
	inspectType = EditorEntityType::Flag;
	sprite = AddComponent<CSpriteComponent>(NAME_OF(sprite));
	sprite->LoadTexture("Resources\\EditorEntities\\Flag.dds");
	sprite->SetRenderRect(XMUINT2(32, 32));
	sprite->SetSpriteSize(XMUINT2(64, 64));
	SetPosition(Vector3(320, 320, -1));
}

void CT_EditorEntity_PlayerStart::Update(float deltaTime)
{
}

CT_EditorEntity_WeaponHolder::CT_EditorEntity_WeaponHolder()
{
	sprite = AddComponent<CSpriteComponent>();

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

void CT_EditorEntity_WeaponHolder::AssignWeapon(char* WeaponID, int Index)
{
	current_item = WeaponID;
	itemSlot = Index;

	Debug::Log("WeaponAssigned: %c | %d", WeaponID, Index);


}

void CT_EditorEntity_WeaponHolder::Update(float deltaTime)
{
}

void CT_EditorEntity_WeaponHolder::InitialiseEntity(int SlotID)
{
}
