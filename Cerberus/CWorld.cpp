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

	std::vector<std::string> temp = storedFile["TileData"];


	std::string Test = temp[0];
	std::cout << "" << std::endl;


	for (int i = 0; i < (mapScale * mapScale); i++)
	{
		Vector3 GridPos = IDToWorldSpace(i);

		int ID = atoi(temp[i].c_str());
		Vector3 TempPos = Vector3(-256 * 2, -256 * 4.5, 0) + Vector3((GridPos.x * tileScale), (GridPos.y * tileScale), 0.0f);

		CTile* Tile = Engine::CreateEntity<CTile>();
		Tile->SetPosition(TempPos);
		Tile->SetScale(0.5, 0.5, 1);
		Tile->ChangeTileID(ID);

		tileConainer[(int)GridPos.x][(int)GridPos.y] = Tile;

	}
	



	
	
	
	
	



}

void CWorld::SetWorldSize(Vector3 Scale)
{
}

Vector3 CWorld::IDToWorldSpace(int ID)
{
	int x = ID % mapScale;
	int y = ID / mapScale;

	return Vector3(x,y, 0.0f);
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//						WORLD FOR EDITOR
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


void CWorld_Editable::SaveWorld(int Slot)
{

	std::ifstream i("Resources/Levels/Level_1.json");


	json SaveData;

	std::vector<std::string> MapData;





	for (int x = 0; x < mapScale; x++)
	{
		for (int y = 0; y < mapScale; y++)
		{
			MapData.push_back(std::to_string(tileConainer[x][y]->GetTileID()));
		}
	}
	

	SaveData["TileData"] = MapData;


	std::ofstream o("Resources/Levels/Level_1.json");
	o << SaveData;


}
