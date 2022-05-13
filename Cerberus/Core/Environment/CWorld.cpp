#include "CWorld.h"
#include "Dependencies/NlohmannJson/json.hpp"
#include <iostream>
#include <fstream>






CWorld::CWorld()
{
	for (int i = 0; i < (mapScale * mapScale); i++)
	{
		tileContainer[i] = nullptr;
	}
}

CWorld::CWorld(int Slot)
{
	for (int i = 0; i < (mapScale * mapScale); i++)
	{
		tileContainer[i] = nullptr;
	}
	LoadWorld(Slot);
}


void CWorld::LoadWorld(int Slot)
{
	//UNREFERENCED_PARAMETER(Slot);

	std::string fileName = "Resources/Levels/Level_" + std::to_string(Slot);
	fileName += ".json";

	std::ifstream file(fileName);


	json storedFile;

	file >> storedFile;

	std::vector<std::string> convertedFile = storedFile["TileData"];
	
	

	std::string Test = convertedFile[0];
	std::cout << "" << std::endl;


	for (int i = 0; i < (mapScale * mapScale); i++)
	{
		Vector3 temp = Vector3((float)(i % mapScale), (float)(i / mapScale), 0);
		Vector2 gridPos = Vector2(temp.x, temp.y);

		int ID = atoi(convertedFile[i].c_str());
		Vector3 tempPos = (Vector3(temp.x, temp.y, 0) * (tileScale * 2));
		
		//tempPos += Vector3(0, 64 * tileScale, 0.0f);

		tempPos.z = 10;



		CTile* Tile = Engine::CreateEntity<CTile>();
		Tile->SetNavID(i);
		Tile->SetPosition(tempPos);
		Tile->SetScale(tileScaleMultiplier);
		Tile->ChangeTileID(ID);

		tileContainer[i] = Tile;

	}
	
	/*
	int enemyCount = storedFile["EnemyCount"];



	for (int i = 0; i < enemyCount; i++)
	{
		int EnemyID = storedFile["Enemy"][i]["Type"];
		int EnemyX = storedFile["Enemy"][i]["Position"]["X"];
		int EnemyY = storedFile["Enemy"][i]["Position"]["Y"];

		CAIController* TempController = Engine::CreateEntity<CAIController>();
		TempController->SetPosition(EnemyX, EnemyY, -1);

		int WaypointList = storedFile["Enemy"][i]["WaypointList"];
		for (int y = 0; y < WaypointList; y++)
		{
			int WaypointX = storedFile["Enemy"][i]["Waypoints"][y]["X"];
			int WaypointY = storedFile["Enemy"][i]["Waypoints"][y]["Y"];
			
			
		}
	}
	*/





	BuildNavigationGrid();


	

}

void CWorld::SetupWorld()
{
}

void CWorld::UnloadWorld()
{
}



void CWorld::BuildNavigationGrid()
{

	for (int i = 0; i < mapScale * mapScale; i++)
	{
		Vector2 Position = Vector2((float)(i % mapScale), (float)((i - (i % mapScale)) / mapScale));

		if (tileContainer[i]->IsWalkable())tileContainer[i]->AddConnectedTile(GridToIndex(Position + Vector2(1, 0)));
		if (tileContainer[i]->IsWalkable())tileContainer[i]->AddConnectedTile(GridToIndex(Position + Vector2(-1, 0)));
		if (tileContainer[i]->IsWalkable())tileContainer[i]->AddConnectedTile(GridToIndex(Position + Vector2(0, -1)));
		if (tileContainer[i]->IsWalkable())tileContainer[i]->AddConnectedTile(GridToIndex(Position + Vector2(0, 1)));

	}


}

std::vector<CTile*> CWorld::GetAllWalkableTiles()
{
	std::vector<CTile*> walkableTiles;

	for (int i = 0; i < mapSize; ++i)
	{
		if (tileContainer[i]->IsWalkable())
		{
			walkableTiles.emplace_back(tileContainer[i]);
		}
	}


	return walkableTiles;
}

std::vector<CTile*> CWorld::GetAllObstacleTiles()
{
	std::vector<CTile*> obstacleTiles;

	for (int i = 0; i < mapSize; ++i)
	{
		if (!tileContainer[i]->IsWalkable())
		{
			obstacleTiles.emplace_back(tileContainer[i]);
		}
	}

	return obstacleTiles;
}


Vector3 CWorld::IndexToGrid(int ID)
{

	int x = ID % mapScale;
	int y = (ID - x) / mapScale;
	return Vector3((float)x,(float)y, 0.0f);
}

int CWorld::GridToIndex(Vector2 Position)
{

	return (int)Position.x + ((int)Position.y * mapScale);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////FUNCTIONS BELOW ARE FOR ADDING NEW ENTITIES THAT ARE VALID WITH EDITOR//////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////



/*
* 
void CWorld::LoadEntity(int Slot, Vector3 Position)
{
	CEntity* SpawnedEntity = nullptr;
	switch (Slot)
	{
	case 1:
		//Spawn the entitiy here. The ID should match the order in the resource folder.
		//Example for what you need to do, replace CEntity with the class you want in this slot.
		SpawnedEntity = Engine::CreateEntity<CEntity>();
		break;
	}

	SpawnedEntity->SetPosition(Position);
	entityList.push_back(SpawnedEntity);
}

*/