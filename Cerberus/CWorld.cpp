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
	std::ifstream i("Resources/Levels/Level_1.json");


	json StoredFile;

	i >> StoredFile;

	



	
	 for (int x = 0; x < mapScale; ++x)
	{
		for (int y = 0; y < mapScale; ++y)
		{
			Vector3 TempPos = Vector3(-256 * 2, -256 * 4.5, 0) + Vector3((x * tileScale), (y * tileScale), 0.0f);
			if (x > 5 && y > 5 && x < 145 && y < 145)
			{

				CTile* Tile = Engine::CreateEntity<CTile>();
				Tile->SetPosition(TempPos);
				Tile->SetScale(0.5, 0.5, 0.5);
				Tile->ChangeTileID(1);
			}
			else
			{
				CTile* Tile = Engine::CreateEntity<CTile>();
				Tile->SetPosition(TempPos);
				Tile->SetScale(0.5, 0.5, 0.5);
				Tile->ChangeTileID(0);
			}
		}
	}
	
	
	



}

void CWorld::SetWorldSize(Vector3 Scale)
{
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

	std::vector<std::string>

	for (int x = 0; x < mapScale; x++)
	{
		for (int y = 0; y < mapScale; y++)
		{




		}
	}
	
}
