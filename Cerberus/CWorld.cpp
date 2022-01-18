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
		Vector3 TempPos = (GridPos * (tileScale * 4));
		TempPos -= Vector3(64 * tileScale, 64 * tileScale, 0);

		CTile* Tile = Engine::CreateEntity<CTile>();
		Tile->SetPosition(TempPos);
		Tile->SetScale(4, 4, 4);
		Tile->ChangeTileID(ID);

		tileContainer[(int)GridPos.x][(int)GridPos.y] = Tile;

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

	GenerateTileMap();


	for (int x = 0; x < mapScale; x++)
	{
		for (int y = 0; y < mapScale; y++)
		{
			MapData.push_back(std::to_string(tileContainer[x][y]->GetTileID()));
		}
	}
	

	SaveData["TileData"] = MapData;


	std::ofstream o("Resources/Levels/Level_1.json");
	o << SaveData;


}

void CWorld_Editable::EditWorld(int Slot)
{
	ClearSpace();

	AdditiveBox(Vector2(0, 0), Vector2(mapScale, mapScale));

	SubtractiveBox(Vector2(5,5), Vector2(mapScale - 5, mapScale - 5));

	AdditiveBox(Vector2(15, 15), Vector2(23, 23));

	//GenerateTileMap();

	SaveWorld(0);
}

void CWorld_Editable::NewWorld(int Slot)
{

	for (int x = 0; x < mapScale; x++)
	{
		for (int y = 0; y < mapScale; y++)
		{
			Vector3 TempPos = (Vector3(x,y,100) * (tileScale * 4));
			TempPos -= Vector3(64 * tileScale, 64 * tileScale, 0);

			CTile* Tile = Engine::CreateEntity<CTile>();
			Tile->SetPosition(TempPos);
			Tile->SetScale(4, 4, 4);
			Tile->ChangeTileID(0);

			tileData[x][y] = Tile;
		}
	}

	for (int x = 0; x < mapScale; x++)
	{
		for (int y = 0; y < mapScale; y++)
		{
			Vector3 TempPos = (Vector3(x, y, 0) * (tileScale * 4));
			TempPos -= Vector3(64 * tileScale, 64 * tileScale, 0);

			CTile* Tile = Engine::CreateEntity<CTile>();
			Tile->SetPosition(TempPos);
			Tile->SetScale(4, 4, 4);
			Tile->ChangeTileID(0);

			tileContainer[x][y] = Tile;
		}
	}

}

void CWorld_Editable::ClearSpace()
{
	for (int x = 0; x < mapScale; x++)
	{
		for (int y = 0; y < mapScale; y++)
		{

			

			tileData[x][y]->ChangeTileID(0);



		}
	}
}

void CWorld_Editable::AdditiveBox(Vector2 A, Vector2 B)
{

	BoxOperation(A, B, 0);

}

void CWorld_Editable::SubtractiveBox(Vector2 A, Vector2 B)
{
	BoxOperation(A, B, 1);
}

void CWorld_Editable::AdditiveBox_Scale(Vector2 A, Vector2 B)
{

	BoxOperation(A, B + A, 0);

}

void CWorld_Editable::SubtractiveBox_Scale(Vector2 A, Vector2 B)
{
	BoxOperation(A, A + B, 1);
}

void CWorld_Editable::BoxOperation(Vector2 A, Vector2 B, int TileID)
{
	Vector2 Dimensions = B - A;
	Vector2 CurrentPos = A;

	
	for (int x = 0; x < Dimensions.x; ++x)
	{
		for (int y = 0; y < Dimensions.y; ++y)
		{

			tileData[((int)CurrentPos.x + x)][(int)CurrentPos.y + y]->ChangeTileID(TileID);



		}
	}

}

void CWorld_Editable::GenerateTileMap()
{

	
	for (int x = 0; x < mapScale; x++)
	{
		for (int y = 0; y < mapScale; y++)
		{
			if (tileData[x][y]->GetTileID() == 0)
			{
				if (IsFloorAdjacent(Vector2(x, y)))
				{
					CellList[x][y] = CellType::Edge;
					
				}
				else if (!IsFloorAdjacent(Vector2(x, y)))
				{
					CellList[x][y] = CellType::Empty;
				}
			}
			else if (tileData[x][y]->GetTileID() == 1)
			{
				CellList[x][y] = CellType::Floor;

			}


		}
	}
	
	 for (int x = 0; x < mapScale; x++)
	{
		for (int y = 0; y < mapScale; y++)
		{
			
			SetCorner(x,y);

		}
	}
	

	for (int x = 0; x < mapScale; x++)
	{
		for (int y = 0; y < mapScale; y++)
		{
			Vector2 FloorResult = FindFloorAdjacent(x, y);
			Vector2 FloorResultDiagonal = FindFloorAdjacentDiagonal(x, y);
			Vector2 EdgeAdjacentResult = FindAdjacents(x,y, CellType::Edge);
			switch (CellList[x][y])
			{
			case CellType::Edge:
				if (FloorResult == Vector2(1, 0)) tileContainer[x][y]->ChangeTileID(CellID::W_S);
				 if (FloorResult == Vector2(-1, 0)) tileContainer[x][y]->ChangeTileID(CellID::W_N);
				 if (FloorResult == Vector2(0, 1)) tileContainer[x][y]->ChangeTileID(CellID::W_E);
				 if (FloorResult == Vector2(0, -1)) tileContainer[x][y]->ChangeTileID(CellID::W_W);
				break;
			case CellType::Empty:
				tileContainer[x][y]->ChangeTileID(CellID::N);
				break;
			case CellType::Floor:
				tileContainer[x][y]->ChangeTileID(CellID::F);
				break;
			case CellType::InnerCorner:
				if (FloorResultDiagonal == Vector2(1, 1)) tileContainer[x][y]->ChangeTileID(CellID::IC_SE);
				else if (FloorResultDiagonal == Vector2(-1, -1)) tileContainer[x][y]->ChangeTileID(CellID::IC_NW);
				else if (FloorResultDiagonal == Vector2(-1, 1)) tileContainer[x][y]->ChangeTileID(CellID::IC_NE);
				else if (FloorResultDiagonal == Vector2(1, -1)) tileContainer[x][y]->ChangeTileID(CellID::IC_SW);
				
				break;
			case CellType::OuterCorner:
				if (FloorResultDiagonal == Vector2(1,1)) tileContainer[x][y]->ChangeTileID(CellID::OC_SE);
				else if (FloorResultDiagonal == Vector2(-1, -1)) tileContainer[x][y]->ChangeTileID(CellID::OC_NW);
				else if (FloorResultDiagonal == Vector2(-1, 1)) tileContainer[x][y]->ChangeTileID(CellID::OC_NE);
				else if (FloorResultDiagonal == Vector2(1, -1)) tileContainer[x][y]->ChangeTileID(CellID::OC_SW);
				
				break;
			}
			

		}
	}






}
