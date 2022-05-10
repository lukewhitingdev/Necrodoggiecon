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
