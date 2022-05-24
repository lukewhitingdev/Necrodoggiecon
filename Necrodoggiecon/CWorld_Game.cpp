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



/**
 * Constructor, automatically loads world based on provided slot.
 * 
 * \param Slot
 * Determines which level to load.
 */
CWorld_Game::CWorld_Game(int Slot)
{
	LoadWorld(Slot);
}

/**  */
void CWorld_Game::SetupWorld()
{
	PlayerController* controller = Engine::CreateEntity<PlayerController>();
	PlayerCharacter* character1 = Engine::CreateEntity<PlayerCharacter>();

	// Locked Camera follows player.
	CCameraComponent* lockedCameraComponent = character1->AddComponent<CCameraComponent>();
	lockedCameraComponent->SetAttachedToParent(true);

	CameraManager::SetRenderingCamera(lockedCameraComponent);

	controller->charOne = character1;

	Vector3 PlayerStart = Vector3(StartPos.x, StartPos.y, 0) * (tileScale * tileScaleMultiplier) + Vector3(0, 0, -1);
	Debug::Log("Player Start Position: [%f | %f]", PlayerStart.x, PlayerStart.y);
	character1->SetPosition(PlayerStart);
	controller->Possess(character1);

	//Please stop configuring stuff in here instead of in the class constructor - Lets not spread configuration to many different places in the project!

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
			break;
		}
		default:
			enemy = Engine::CreateEntity<CAIController>();
			break;
		}

		int waypointlist = storedFile["Enemy"][i]["WaypointList"];
		for (int y = 0; y < waypointlist; y++)
		{
			int waypointx = storedFile["Enemy"][i]["Waypoints"][y]["X"];
			int waypointy = storedFile["Enemy"][i]["Waypoints"][y]["Y"];
			Vector3 patrolPosition = Vector3{ (float)waypointx * mapScale * tileScaleMultiplier, (float)waypointy * mapScale * tileScaleMultiplier, 0.0f };
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
				patrolNodes[patrolIndex]->nextPatrolNode = patrolNodes[patrolIndex+1];
			}
		}
		Vector3 enemyPos = enemy->GetPosition();
		enemy->pathing->SetPatrolNodes(patrolNodes);
		enemy->pathing->currentPatrolNode = enemy->pathing->FindClosestPatrolNode(enemy->GetPosition());
		enemy->SetCurrentState(PatrolState::getInstance());
		patrolNodes.clear();


	}
}
