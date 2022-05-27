/*******************************************************************
 * \file   CWorld.cpp
 * \brief  Base class for the game's levels. contains all logic required for loading in and unloading a level while also containing a list of entities to be spawned in.
 * 
 * \author Samuel Elliot Jackson
 * \date   May 2022
 *********************************************************************/
#include "CWorld.h"
#include "Dependencies/NlohmannJson/json.hpp"
#include <iostream>
#include <fstream>
#include <Cerberus\Core\Components\CCameraComponent.h>
#include "Cerberus/Core/Utility/CameraManager/CameraManager.h"
#include <Cerberus/Core/Structs/CCamera.h>

/**
 * Standard constructor.
 * 
 */
CWorld::CWorld()
{
	
	for (int i = 0; i < (mapScale * mapScale); i++)
	{
		tileContainer[i] = nullptr;
	}
	//EntityManager::Purge();
}

/** Constructor that takes in the World's slot */
CWorld::CWorld(int Slot)
{
	for (int i = 0; i < (mapScale * mapScale); i++)
	{
		tileContainer[i] = nullptr;
	}
	LoadWorld(Slot);
}
/**
 * Loads in the world from provided file.
 * 
 * \param Slot
 */

void CWorld::LoadWorld(int Slot)
{
	//UNREFERENCED_PARAMETER(Slot);

	mapSlot = Slot;

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
	
	
	
	
	StartPos.x = storedFile["PlayerStart"]["X"];
	StartPos.y = storedFile["PlayerStart"]["Y"];





	BuildNavigationGrid();


	

}

/**
 * Used by derivative classes, primary method to setup any assets needed by all levels (PlayerCharacter, PlayerController, Cameras etc).
 * 
 */
void CWorld::SetupWorld()
{
	
}

/**
 * Used by derivative classes, Primary method for unloading the world
 * 
 */
void CWorld::UnloadWorld()
{
}

/**
 * Used by derivative classes, primary method for reloading levels.
 * 
 */
void CWorld::ReloadWorld()
{
}

/**
 * Destroys the tile's within the world.
 * 
 */
void CWorld::DestroyWorld()
{
	UnloadWorld();
	for (int i = 0; i < mapScale * mapScale; i++)
	{
		Engine::DestroyEntity(tileContainer[i]);
	}
}

/**
 * Generates the grid's navigation grid for the AI system.
 * 
 */
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

/**
 * Used by derivative classes to load in entities that are unique to the game.
 * 
 * \param Slot
 */
void CWorld::LoadEntities(int Slot)
{
}

/**
 * Gets all walkable tiles.
 * 
 * \return returns an array of walkable tiles
 */
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
/**
 * Gets a list of all unwalkable tiles.
 * 
 * \return List of unwalkable tiles
 */
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
/**
 * Index to Grid.
 * 
 * \param ID Input ID
 * \return returns a position within the grid that is equivalent to the ID.
 */

Vector3 CWorld::IndexToGrid(int ID)
{

	int x = ID % mapScale;
	int y = (ID - x) / mapScale;
	return Vector3((float)x,(float)y, 0.0f);
}

/**
 * Grid to Index.
 * 
 * \param Position Vector position inside grid.
 * \return Equivalent Index that coresponds to the Position
 */
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