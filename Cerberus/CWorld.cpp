#include "CWorld.h"
#include "Libraries/json.hpp"
#include <iostream>
#include <fstream>




CWorld::CWorld()
{
}

CWorld::CWorld(int WorldSlot)
{


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
		Vector3 temp = Vector3(i % mapScale, i / mapScale, 0);
		Vector2 gridPos = Vector2(temp.x, temp.y);

		int ID = atoi(convertedFile[i].c_str());
		Vector3 tempPos = (Vector3(temp.x, temp.y, 0) * (tileScale * 2));
		tempPos -= Vector3(64 * tileScale, 64 * tileScale, 0);

		tempPos += Vector3(0, 128 * tileScale, 0);



		CTile* Tile = Engine::CreateEntity<CTile>();
		Tile->SetPosition(tempPos);
		Tile->SetScale(2, 2, 2);
		Tile->ChangeTileID(ID);

		tileContainer[i] = Tile;

	}
	



	
	
	
	
	



}

void CWorld::SetWorldSize(Vector3 Scale)
{
}

void CWorld::BuildNavigationGrid()
{

	for (int i = 0; i < mapScale * mapScale; i++)
	{
		Vector2 Position = Vector2(i % mapScale, ((i - (i % mapScale)) / mapScale));

		if (tileContainer[i]->IsWalkable())tileContainer[i]->AddConnectedTile(GridToIndex(Position + Vector2(1, 0)));
		if (tileContainer[i]->IsWalkable())tileContainer[i]->AddConnectedTile(GridToIndex(Position + Vector2(-1, 0)));
		if (tileContainer[i]->IsWalkable())tileContainer[i]->AddConnectedTile(GridToIndex(Position + Vector2(0, -1)));
		if (tileContainer[i]->IsWalkable())tileContainer[i]->AddConnectedTile(GridToIndex(Position + Vector2(0, 1)));

	}


}

Vector3 CWorld::IndexToGrid(int ID)
{



	float x = ID % mapScale;



	float y = (ID - x) / mapScale;


	//Vector2 ReturnValue = Vector2(ID % mapScale, (ID - (ID % mapScale)) / mapScale);

	return Vector3(x,y, 0.0f);
}

int CWorld::GridToIndex(Vector2 Position)
{

	return (int)Position.x + ((int)Position.y * mapScale);
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//						WORLD FOR EDITOR
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

