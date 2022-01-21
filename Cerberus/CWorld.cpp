#include "CWorld.h"
#include "Libraries/json.hpp"
#include <iostream>
#include <fstream>

CTile* CWorld::tileContainer[mapScale * mapScale];


CWorld::CWorld()
{
	for (int i = 0; i < (mapScale * mapScale); i++)
	{
		tileContainer[i] = nullptr;
	}
}


void CWorld::LoadWorld(int Slot)
{
	std::ifstream file("Resources/Levels/Level_1.json");


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
		tempPos -= Vector3((mapScale * tileScale), (mapScale * tileScale), 0);

		//tempPos += Vector3(0, 64 * tileScale, 0.0f);

		tempPos.z = 10;



		CTile* Tile = Engine::CreateEntity<CTile>();
		Tile->SetNavID(i);
		Tile->SetPosition(tempPos);
		Tile->SetScale(2, 2, 2);
		Tile->ChangeTileID(ID);

		tileContainer[i] = Tile;

	}
	

	BuildNavigationGrid();


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

	for (int i = 0; i < (mapScale * mapScale); ++i)
	{
		if (tileContainer[i]->IsWalkable())
		{
			walkableTiles.emplace_back(tileContainer[i]);
		}
	}


	return walkableTiles;
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


