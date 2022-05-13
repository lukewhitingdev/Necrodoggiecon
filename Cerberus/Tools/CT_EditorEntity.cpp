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
	InspectType = EditorEntityType::Standard;
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

CT_EditorEntity_Enemy::CT_EditorEntity_Enemy()
{
	sprite = AddComponent<CSpriteComponent>();
	InspectType = EditorEntityType::Enemy;


}

void CT_EditorEntity_Enemy::Update(float deltaTime)
{
}

void CT_EditorEntity_Enemy::InitialiseEntity(int SlotID)
{
	EntitySlotID = SlotID;
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
	TempWaypoint->GridPos = Position;
	TempWaypoint->WaypointOrder = Waypoints.size();
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
}

CT_EditorEntity_Waypoint::CT_EditorEntity_Waypoint()
{
	InspectType = EditorEntityType::Waypoint;
	sprite = AddComponent<CSpriteComponent>();
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
