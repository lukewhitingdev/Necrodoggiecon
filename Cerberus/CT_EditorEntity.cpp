#include "CT_EditorEntity.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include "Core/Components/CSpriteComponent.h"
#include <WorldConstants.h>




CT_EditorEntity::CT_EditorEntity()
{
}

void CT_EditorEntity::Update(float deltaTime)
{
}

void CT_EditorEntity::InitialiseEntity(int SlotID)
{


	
}

void CT_EditorEntity::SaveEntity()
{
}

CT_EditorEntity_Enemy::CT_EditorEntity_Enemy()
{
	sprite = AddComponent<CSpriteComponent>();


}

void CT_EditorEntity_Enemy::Update(float deltaTime)
{
}

void CT_EditorEntity_Enemy::InitialiseEntity(int SlotID)
{

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

void CT_EditorEntity_Enemy::SaveEntity()
{

}
