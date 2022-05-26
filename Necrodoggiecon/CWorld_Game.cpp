/*******************************************************************
 * \file   CWorld_Game.cpp
 * \brief  Child class of CWorld created for the game, overrides world setup from parent.
 * 
 * \author Samuel Elliot Jackson
 * \date   May 2022
 *********************************************************************/
#include "CWorld_Game.h"
#include <Necrodoggiecon\Game\PlayerController.h>
#include <Necrodoggiecon\Game\PlayerCharacter.h>
#include <Cerberus\Core\Components\CCameraComponent.h>
#include "Cerberus/Core/Utility/CameraManager/CameraManager.h"
#include <Cerberus/Core/Structs/CCamera.h>
#include "Cerberus/WorldConstants.h"
#include "Necrodoggiecon/PauseMenu.h"
#include "Cerberus/Core/Utility/CUIManager.h"
#include <Necrodoggiecon\Game\CInteractable.h>
#include <Game/WeaponPickup.h>
#include <Weapons/Melee/Dagger.h>
#include <Weapons/Melee/Rapier.h>
#include <Weapons/Melee/Longsword.h>
#include <Weapons/Ranged/Crossbow.h>
#include <Weapons/Ranged/Fireball.h>
#include <Weapons/Ranged/MagicMissile.h>



/**
 * Constructor, automatically loads world based on provided slot.
 * 
 * \param Slot
 * Determines which level to load.
 */
CWorld_Game::CWorld_Game(int Slot)
{
	mapSlot = Slot;
	LoadWorld(Slot);
}

/**  */
void CWorld_Game::SetupWorld()
{
	PlayerController* controller = Engine::CreateEntity<PlayerController>();

	PlayerCharacter* character1 = Engine::CreateEntity<PlayerCharacter>();
	//EntityList.push_back(character1);
	EntityList.push_back(controller);

	// Locked Camera follows player.
	CCameraComponent* lockedCameraComponent = character1->AddComponent<CCameraComponent>(NAME_OF(spriteComponentLegs));
	lockedCameraComponent->SetAttachedToParent(true);



	CameraManager::AddCamera(lockedCameraComponent);

	CameraManager::SetRenderingCamera(lockedCameraComponent);


	CUIManager::AddCanvas(Engine::CreateEntity<PauseMenu>(), "PauseMenu");

	controller->charOne = character1;

	Vector3 PlayerStart = Vector3(StartPos.x, StartPos.y, 0) * (tileScale * tileScaleMultiplier) + Vector3(0, 0, -1);
	Debug::Log("Player Start Position: [%f | %f]", PlayerStart.x, PlayerStart.y);
	character1->SetPosition(PlayerStart);
	controller->Possess(character1);

	//Please stop configuring stuff in here instead of in the class constructor - Lets not spread configuration to many different places in the project!

	LoadEnemyUnits(mapSlot);
	LoadEntities(mapSlot);

	

}

void CWorld_Game::UnloadWorld()
{
	for (int i = 0; i < EntityList.size(); i++)
	{
		if (EntityList[i] != nullptr)
		{
			Engine::DestroyEntity(EntityList[i]);
		}
	}
}

void CWorld_Game::ReloadWorld()
{
	for (int i = 0; i < EntityList.size(); i++)
	{
		if (EntityList[i] != nullptr)
		{
			Engine::DestroyEntity(EntityList[i]);
		}
	}
	SetupWorld();
	LoadEnemyUnits(mapSlot);
	LoadEntities(mapSlot);
}

void CWorld_Game::LoadEnemyUnits(int Slot)
{
	std::string fileName = "Resources/Levels/Level_" + std::to_string(mapSlot);
	fileName += ".json";

	std::ifstream file(fileName);

	json storedFile;

	file >> storedFile;

	int enemyCount = storedFile["EnemyCount"];

	std::vector<PatrolNode*> patrolNodes;

	for (int i = 0; i < enemyCount; i++)
	{
		int EnemyID = storedFile["Enemy"][i]["Type"];
		int EnemyX = storedFile["Enemy"][i]["Position"]["X"];
		int EnemyY = storedFile["Enemy"][i]["Position"]["Y"];
		Vector3 position = Vector3{ (float)EnemyX, (float)EnemyY, 0.0f };
		int WeaponID = storedFile["Enemy"][i]["WeaponIndex"];
		CAIController* enemy = nullptr;

		switch (EnemyID)
		{
		case 0:
		{
			enemy = Engine::CreateEntity<DogEnemy>();
			enemy->SetPosition(position);
			break;
		}
		case 1:
		{
			enemy = Engine::CreateEntity<GruntEnemy>();
			enemy->SetPosition(position);
			
			switch (WeaponID)
			{
			case 0:
				enemy->EquipWeapon(new Dagger());
				break;
			case 1:
				enemy->EquipWeapon(new Rapier());
				break;
			case 2:
				enemy->EquipWeapon(new Longsword());
				break;
			case 3:
				enemy->EquipWeapon(new Crossbow());
				break;
			case 4:
				enemy->EquipWeapon(new MagicMissile());
				break;
			case 5: 
				enemy->EquipWeapon(new Fireball());
				break;

			}
			
			break;
		}
		default:
			enemy = Engine::CreateEntity<CAIController>();
			break;
		}
		EntityList.push_back(enemy);

		int waypointlist = storedFile["Enemy"][i]["WaypointList"];
		for (int y = 0; y < waypointlist; y++)
		{
			int waypointx = storedFile["Enemy"][i]["Waypoints"][y]["X"];
			int waypointy = storedFile["Enemy"][i]["Waypoints"][y]["Y"];
			Vector3 patrolPosition = Vector3{ (float)waypointx * (tileScale * tileScaleMultiplier), (float)waypointy * (tileScale * tileScaleMultiplier), 0.0f };
			PatrolNode* patrol = new PatrolNode(patrolPosition);
			patrolNodes.push_back(patrol);
		}

		int numberOfPatrolNodes = patrolNodes.size();
		for (int patrolIndex = 0; patrolIndex < numberOfPatrolNodes; ++patrolIndex)
		{
			if (patrolIndex == numberOfPatrolNodes - 1)
			{
				patrolNodes[patrolIndex]->nextPatrolNode = patrolNodes[0];
			}
			else
			{
				patrolNodes[patrolIndex]->nextPatrolNode = patrolNodes[patrolIndex + 1];
			}
		}
		Vector3 enemyPos = enemy->GetPosition();
		enemy->pathing->SetPatrolNodes(patrolNodes);
		enemy->pathing->currentPatrolNode = enemy->pathing->FindClosestPatrolNode(enemy->GetPosition());
		enemy->SetCurrentState(PatrolState::getInstance());
		patrolNodes.clear();


	}
}

void CWorld_Game::LoadEntities(int Slot)
{

	std::string fileName = "Resources/Levels/Level_" + std::to_string(mapSlot);
	fileName += ".json";

	std::ifstream file(fileName);

	json storedFile;

	file >> storedFile;

	int TotalWeaponHolders = storedFile["TotalWeaponHolders"];
	for (int i = 0; i < TotalWeaponHolders; i++)
	{
		
		int HolderX = storedFile["WeaponHolder"][i]["X"];
		int HolderY = storedFile["WeaponHolder"][i]["Y"];
		int WepID = storedFile["WeaponHolder"][i]["WeaponIndex"];
		
		switch (WepID)
		{
		case 0:
			Engine::CreateEntity<WeaponPickup<Dagger>>()->SetPosition((Vector3(HolderX, HolderY, 0.0f) * (tileScale * tileScaleMultiplier)));
			break;
		case 1:
			Engine::CreateEntity<WeaponPickup<Rapier>>()->SetPosition((Vector3(HolderX, HolderY, 0.0f) * (tileScale * tileScaleMultiplier)) );
			break;
		case 2:
			Engine::CreateEntity<WeaponPickup<Longsword>>()->SetPosition((Vector3(HolderX, HolderY, 0.0f) * (tileScale * tileScaleMultiplier)) );
			break;
		case 3:
			Engine::CreateEntity<WeaponPickup<Crossbow>>()->SetPosition((Vector3(HolderX, HolderY, 0.0f) * (tileScale * tileScaleMultiplier)) );
			break;
		case 4:
			Engine::CreateEntity<WeaponPickup<Fireball>>()->SetPosition((Vector3(HolderX, HolderY, 0.0f) * (tileScale * tileScaleMultiplier)) );
			break;
		case 5:
			Engine::CreateEntity<WeaponPickup<MagicMissile>>()->SetPosition((Vector3(HolderX, HolderY, 0.0f) * (tileScale * tileScaleMultiplier)) );
			break;

		}



		
		
		
		
		
		
		//Engine::CreateEntity<WeaponPickup<ShieldScroll>>()->SetPosition(800.0f, 400, 0.0f);
		//Engine::CreateEntity<WeaponPickup<InvisibilityScroll>>()->SetPosition(800.0f, 450, 0.0f);
	}
}
