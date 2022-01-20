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
		Vector3 Temp = Vector3(i % mapScale, i / mapScale, 0);
		Vector2 GridPos = Vector2(Temp.x, Temp.y);

		int ID = atoi(temp[i].c_str());
		Vector3 TempPos = (Vector3(Temp.x, Temp.y, 0) * (tileScale * 4));
		TempPos -= Vector3(64 * tileScale, 64 * tileScale, 0);

		CTile* Tile = Engine::CreateEntity<CTile>();
		Tile->SetPosition(TempPos);
		Tile->SetScale(4, 4, 4);
		Tile->ChangeTileID(ID);

		tileContainer[i] = Tile;

	}
	



	
	
	
	
	



}

void CWorld::SetWorldSize(Vector3 Scale)
{
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


void CWorld_Editable::SaveWorld(int Slot)
{

	std::ifstream i("Resources/Levels/Level_1.json");


	json SaveData;

	std::vector<std::string> MapData;

	GenerateTileMap();


	for (int i = 0; i < mapScale * mapScale; i++)
	{
		MapData.push_back(std::to_string(tileContainer[i]->GetTileID()));
	}
	

	SaveData["TileData"] = MapData;


	std::ofstream o("Resources/Levels/Level_1.json");
	o << SaveData;


}

void CWorld_Editable::EditWorld(int Slot)
{
	ClearSpace();

	//AdditiveBox(Vector2(0, 0), Vector2(mapScale, mapScale));

	SubtractiveBox(Vector2(5,5), Vector2(mapScale - 5, mapScale - 5));

	AdditiveBox(Vector2(15, 15), Vector2(23, 23));

	GenerateTileMap();

	SaveWorld(0);
}

void CWorld_Editable::NewWorld(int Slot)
{

	for (int i = 0; i < mapScale * mapScale; i++)
	{
		Vector3 ConvertedPos = IndexToGrid(i);
		Vector3 TempPos = (Vector3(ConvertedPos.x, ConvertedPos.y, -25) * (tileScale * 4));


		TempPos -= Vector3(64 * tileScale, 64 * tileScale, 0);
		TempPos += Vector3(50000000, 0, 0);

		CTile* Tile = Engine::CreateEntity<CTile>();
		Tile->SetPosition(TempPos);
		Tile->SetScale(4, 4, 4);
		Tile->ChangeTileID(0);

		tileData[i] = Tile;
	}

	for (int i = 0; i < mapScale * mapScale; i++)
	{
		Vector3 ConvertedPos = IndexToGrid(i);
		Vector3 TempPos = (Vector3(ConvertedPos.x, ConvertedPos.y, 0) * (tileScale * 4));
		TempPos -= Vector3(64 * tileScale, 64 * tileScale, 0);

		CTile* Tile = Engine::CreateEntity<CTile>();
		Tile->SetPosition(TempPos);
		Tile->SetScale(4, 4, 4);
		Tile->ChangeTileID(0);

		tileContainer[i] = Tile;
	}

}




void CWorld_Editable::ClearSpace()
{
	for (int i = 0; i < mapScale * mapScale; i++)
	{
		tileData[i]->ChangeTileID(0);
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




	
	for (int x = 0; x < Dimensions.x; x++)
	{
		for (int y = 0; y < Dimensions.y; y++)
		{
			Vector3 Pos = Vector3((float)x, (float)y, 0);
		


			int Index = (x + A.x) + ((y + A.y) * mapScale);
			CTile* Ref = tileData[Index];
			if (A.x + x > 0 && A.x + x < mapScale && A.y + y > 0 && A.y + y < mapScale)
				Ref->ChangeTileID(TileID);


		}
	}

}

void CWorld_Editable::GenerateTileMap()
{

	
	for (int i = 0; i < mapScale * mapScale; i++)
	{
		if (tileData[i]->GetTileID() == 0)
		{
			Vector2 Pos = Vector2(i % mapScale, i / mapScale);

			if (IsFloorAdjacent(Vector2(Pos.x, Pos.y)))
			{
				CellList[i] = CellType::Edge;
			}
			else CellList[i] = CellType::Empty;

		}
		else if (tileData[i]->GetTileID() == 1)
		{
			CellList[i] = CellType::Floor;
		}

	}
	
	 for (int i = 0; i < mapScale * mapScale; i++)
	{

		 Vector3 Temp = IndexToGrid(i);
		 if (IsTile(Vector2(Temp.x, Temp.y), CellType::Edge))
		 {

			 int Do = 0;

		 }
		 SetCorner(Vector2(Temp.x, Temp.y));

	}
	

	for (int i = 0; i < mapScale * mapScale; i++)
	{
		Vector3 Temp = IndexToGrid(i);

		//Vector3 Test = Vector3(1, 9, 0);


		Vector2 Pos = Vector2(Temp.x, Temp.y);
		Vector2 FloorResult = FindAdjacents(Pos, CellType::Floor);
		Vector2 FloorResultDiagonal = FindFloorAdjacentDiagonal(Pos);
		Vector2 EdgeAdjacentResult = FindAdjacents(Pos, CellType::Edge);

		switch (CellList[i])
		{
		case CellType::Edge:

			
			if (FloorResult == Vector2(0, -1)) tileContainer[i]->ChangeTileID(CellID::W_N);
			else if (FloorResult == Vector2(0, 1)) tileContainer[i]->ChangeTileID(CellID::W_S);
			else if (FloorResult == Vector2(1, 0)) tileContainer[i]->ChangeTileID(CellID::W_W);
			else if (FloorResult == Vector2(-1, 0)) tileContainer[i]->ChangeTileID(CellID::W_E);
			break;
		case CellType::Empty:
			tileContainer[i]->ChangeTileID(CellID::N);
			break;
		case CellType::Floor:
			tileContainer[i]->ChangeTileID(CellID::F);
			break;
		case CellType::InnerCorner:

			

			if (EdgeAdjacentResult == Vector2(1,-1)) tileContainer[i]->ChangeTileID(CellID::IC_NW);
			if (EdgeAdjacentResult == Vector2(-1, -1)) tileContainer[i]->ChangeTileID(CellID::IC_NE);
			if (EdgeAdjacentResult == Vector2(-1, 1)) tileContainer[i]->ChangeTileID(CellID::IC_SW);
			if (EdgeAdjacentResult == Vector2(1, 1)) tileContainer[i]->ChangeTileID(CellID::IC_SE);


			break;
		case CellType::OuterCorner:

			if (FloorResultDiagonal == Vector2(1, -1)) tileContainer[i]->ChangeTileID(CellID::OC_NW);
			else if (FloorResultDiagonal == Vector2(-1, -1)) tileContainer[i]->ChangeTileID(CellID::OC_NE);
			else if (FloorResultDiagonal == Vector2(-1, 1)) tileContainer[i]->ChangeTileID(CellID::OC_SE);
			else if (FloorResultDiagonal == Vector2(1, 1)) tileContainer[i]->ChangeTileID(CellID::OC_SW);

			break;
		}
	}






}

bool CWorld_Editable::IsFloorAdjacent(Vector2 Position)
{
	if (Position.x > 1 && Position.y > 1 && Position.x < mapScale - 1 && Position.y < mapScale - 1)
	{

		int Pos = GridToIndex(Position);

		
		return (tileData[GridToIndex(Position + Vector2(1, 0))]->GetTileID() == 1 ||
			tileData[GridToIndex(Position + Vector2(-1, 0))]->GetTileID() == 1 ||
			tileData[GridToIndex(Position + Vector2(0, 1))]->GetTileID() == 1 ||
			tileData[GridToIndex(Position + Vector2(0, -1))]->GetTileID() == 1 ||

			tileData[GridToIndex(Position + Vector2(1, 1))]->GetTileID() == 1 ||
			tileData[GridToIndex(Position + Vector2(-1, -1))]->GetTileID() == 1 ||
			tileData[GridToIndex(Position + Vector2(1, -1))]->GetTileID() == 1 ||
			tileData[GridToIndex(Position + Vector2(-1, 1))]->GetTileID() == 1);
	}
	else return false;
}

Vector2 CWorld_Editable::FindAdjacents(Vector2 Pos, CellType ID)
{

	int X;
	int Y;
	if (CellList[GridToIndex(Pos + Vector2(1, 0))] == ID)
	{
		X = 1;
		if (CellList[GridToIndex(Pos + Vector2(-1, 0))] == ID) X = 2;
	}
	else if (CellList[GridToIndex(Pos + Vector2(-1, 0))] == ID)
	{
		X = -1;
	}
	else
		X = 0;

	if (CellList[GridToIndex(Pos + Vector2(0, 1))] == ID)
	{
		Y = 1;
		if (CellList[GridToIndex(Pos + Vector2(1, -1))] == ID) Y = 2;
	}
	else if (CellList[GridToIndex(Pos + Vector2(0, -1))] == ID)
	{
		Y = -1;
	}
	else Y = 0;




	return Vector2(X,Y);
}
