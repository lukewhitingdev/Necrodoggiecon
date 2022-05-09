#include "CWorld_Edit.h"
#include "Dependencies/NlohmannJson/json.hpp"
#include <iostream>
#include <fstream>



CellData CWorld_Editable::tileData[mapScale * mapScale];
EditOperationMode CWorld_Editable::operationType = EditOperationMode::None;
Vector2 CWorld_Editable::editOrigin = Vector2(0, 0);
bool CWorld_Editable::selectedCell = false;
bool CWorld_Editable::isQueueLocked = false;


void CWorld_Editable::SetOperationMode(EditOperationMode mode)
{
	operationType = mode;
	switch (mode)
	{
	case EditOperationMode::Additive:
		Debug::Log("OperationMode: Additive");
		break;
	case EditOperationMode::Subtractive:
		Debug::Log("OperationMode: Subtractive");
		break;
	case EditOperationMode::None:
		Debug::Log("OperationMode: None");
		break;
	}
}

void CWorld_Editable::QueueCell(Vector2 Cell)
{
	if (operationType == EditOperationMode::Additive_Single || operationType == EditOperationMode::Subtractive_Single)
	{
		editOrigin = Cell;
		PerformOperation(editOrigin, Cell);
	}
	else
	{
		if (!isQueueLocked)
		{
			if (!selectedCell)
			{
				editOrigin = Cell;
				selectedCell = true;
			}
			else
			{


				PerformOperation(editOrigin, Cell);

				selectedCell = false;
			}
		}
	}

}

void CWorld_Editable::ClearQueue()
{
	
	editOrigin = Vector2(0, 0);
	selectedCell = false;
}

void CWorld_Editable::PerformOperation(Vector2 A, Vector2 B)
{


	Debug::Log("Called Operation");

	switch (operationType)
	{
	case EditOperationMode::Additive:
		AdditiveBox(A, B);
		break;
	case EditOperationMode::Subtractive:
		SubtractiveBox(A,B);
		break;
	case EditOperationMode::Subtractive_Single:
		Subtractive_Cell(A);
		break;
	case EditOperationMode::Additive_Single:
		Additive_Cell(A);
		break;
	case EditOperationMode::None:
		break;

	}
	ClearQueue();

	GenerateTileMap();
}

void CWorld_Editable::PerformOperation_ClearSpace()
{
	ClearSpace();
	GenerateTileMap();
}

void CWorld_Editable::LoadWorld_Edit()
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

		//tempPos += Vector3(0, 64 * tileScale, 0.0f);

		tempPos.z = 10;



		CTile* Tile = Engine::CreateEntity<CTile>();
		Tile->SetPosition(tempPos);
		Tile->SetScale(tileScaleMultiplier);
		Tile->ChangeTileID(ID);

		tileContainer[i] = Tile;



		if (Tile->GetTileID() != 1)
		{
			tileData[i].id = 0;
		}
		else tileData[i].id = 1;


		//tileData[i].id = Tile->GetTileID();
		tileData[i].type = CellType::Empty;


		

	}

	

	BuildNavigationGrid();

	GenerateTileMap();
}




void CWorld_Editable::SaveWorld(int Slot)
{
	UNREFERENCED_PARAMETER(Slot);
	std::ifstream loadedData("Resources/Levels/Level_1.json");


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
	UNREFERENCED_PARAMETER(Slot);
	ClearSpace();

	
}

void CWorld_Editable::NewWorld(int Slot)
{
	UNREFERENCED_PARAMETER(Slot);
	for (int i = 0; i < mapScale * mapScale; i++)
	{
		Vector3 ConvertedPos = IndexToGrid(i);
		

		tileData[i].id = 0;
		tileData[i].type= CellType::Empty;

	}

	for (int i = 0; i < mapScale * mapScale; i++)
	{
		Vector3 convertedPos = IndexToGrid(i);
		Vector3 tempPos = (Vector3(convertedPos.x, convertedPos.y, 0) * (tileScale * 2));
	


		CTile* tile = Engine::CreateEntity<CTile>();
		tile->SetPosition(tempPos);
		tile->SetScale(tileScaleMultiplier);
		tile->ChangeTileID(0);

		tileContainer[i] = tile;
	}

}

void CWorld_Editable::ToggleDebugMode(bool isDebug)
{
	for (int i = 0; i < mapScale * mapScale; i++)
	{
		tileContainer[i]->SetDebugMode(isDebug);
	}
}




void CWorld_Editable::ClearSpace()
{
	for (int i = 0; i < mapScale * mapScale; i++)
	{
		tileData[i].id = 0;
	}
}
void CWorld_Editable::Additive_Cell(Vector2 A)
{
	int Index = (A.x) + (((int)A.y) * mapScale);
	tileData[Index].id = 0;

}

void CWorld_Editable::Subtractive_Cell(Vector2 A)
{
	int Index = (A.x) + (((int)A.y) * mapScale);
	tileData[Index].id = 1;

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
	Vector2 dimensions = B - A;

	int yMultiplier = 1;
	int xMultiplier = 1;

	if (dimensions.x < 0)
	{
		xMultiplier = -1;
		
	}
	if (dimensions.y < 0)
	{
		yMultiplier = -1;
	
	}


	Debug::Log("Additive Operation: [%f | %f]", dimensions.x, dimensions.y);

	for (int x = 0; x != dimensions.x; x+=xMultiplier)
	{
		for (int y = 0; y != dimensions.y; y+=yMultiplier)
		{
			Vector3 Pos = Vector3((float)x, (float)y, 0);



			int Index = (x + (int)A.x) + ((y + (int)A.y) * mapScale);
			
			if (A.x + x > 0 && A.x + x < mapScale && A.y + y > 0 && A.y + y < mapScale)
				tileData[Index].id = TileID;


		}
	}

}


void CWorld_Editable::GenerateTileMap()
{
	//Initialises the standard tile distribution between floors, Edges and empty

	for (int i = 0; i < mapScale * mapScale; i++)
	{
		if (tileData[i].id == 0)
		{
			Vector2 pos = Vector2((float)(i % mapScale), (float)(i / mapScale));

			if (IsFloorAdjacent(Vector2(pos.x, pos.y)))
			{
				tileData[i].type = CellType::Edge;
			}
			else tileData[i].type = CellType::Empty;

		}
		else if (tileData[i].id == 1)
		{
			tileData[i].type = CellType::Floor;
		}

	}
	
	//Locates corners and assigns them
	std::vector<Vector2> CornerPos;
	for (int i = 0; i < mapScale * mapScale; i++)
	{
		Vector3 pos = IndexToGrid(i);
		Vector2 p2 =  Vector2(pos.x, pos.y);
	
		if (IsTile(p2, CellType::Edge))
		{
			if (GetTotalAdjacentsOfType(p2, CellType::Edge) <= 3)
			{
				Vector2 Dir = FindAdjacentEdges(p2);
				if (Dir.x != 2 && Dir.y != 2)
				{
					CornerPos.push_back(p2);
				}

			}
			
		}
		

	}
	for (int i = 0; i < CornerPos.size(); i++)
	{
		tileData[GridToIndex(CornerPos[i])].type = CellType::InnerCorner;
	}



	for (int i = 0; i < mapScale * mapScale; i++)
	{
		Vector3 pos = IndexToGrid(i);
		Vector2 p2 = Vector2(pos.x, pos.y);
		if (IsTile(p2, CellType::InnerCorner))
		{
			if (GetTotalAdjacentsOfType(p2, CellType::Edge) == 3)
			{
				tileData[GridToIndex(p2)].type = CellType::TConnector;
			}
			else if (GetTotalAdjacentsOfType(p2, CellType::Edge) == 4)
			{
				tileData[GridToIndex(p2)].type = CellType::XConnector;
			}
		}
	}


	for (int i = 0; i < mapScale * mapScale; i++)
	{
		Vector3 pos = IndexToGrid(i);
		if (IsTile(Vector2(pos.x, pos.y), CellType::InnerCorner))
		{
			SetCorner(Vector2(pos.x, pos.y));
		}


	}

	

	
	
	//Assigns all the tiles based on their neighbours and assigned type

	for (int i = 0; i < mapScale * mapScale; i++)
	{
		Vector3 temp = IndexToGrid(i);

		//Vector3 Test = Vector3(1, 9, 0);


		Vector2 Pos = Vector2(temp.x, temp.y);
		Vector2 floorResult = FindAdjacents(Pos, CellType::Floor);
		Vector2 floorResultDiagonal = FindFloorAdjacentDiagonal(Pos);
		std::vector<CellType> TypeList;
		TypeList.push_back(CellType::Edge);
		TypeList.push_back(CellType::InnerCorner);
		TypeList.push_back(CellType::OuterCorner);
		Vector2 edgeAdjacentResult = FindAdjacentEdges(Pos);

		switch (tileData[i].type)
		{
		case CellType::Edge:


			if (floorResult == Vector2(0, -1)) tileContainer[i]->ChangeTileID(CellID::W_N);
			else if (floorResult == Vector2(0, 1)) tileContainer[i]->ChangeTileID(CellID::W_S);
			else if (floorResult == Vector2(1, 0)) tileContainer[i]->ChangeTileID(CellID::W_W);
			else if (floorResult == Vector2(-1, 0)) tileContainer[i]->ChangeTileID(CellID::W_E);
			break;
		case CellType::Empty:
			tileContainer[i]->ChangeTileID(CellID::N);
			break;
		case CellType::Floor:
			tileContainer[i]->ChangeTileID(CellID::F);
			break;
		case CellType::InnerCorner:



			if (edgeAdjacentResult == Vector2(1, -1)) tileContainer[i]->ChangeTileID(CellID::IC_NW);
			if (edgeAdjacentResult == Vector2(-1, -1)) tileContainer[i]->ChangeTileID(CellID::IC_NE);
			if (edgeAdjacentResult == Vector2(-1, 1)) tileContainer[i]->ChangeTileID(CellID::IC_SW);
			if (edgeAdjacentResult == Vector2(1, 1)) tileContainer[i]->ChangeTileID(CellID::IC_SE);


			break;
		case CellType::OuterCorner:

			if (floorResultDiagonal == Vector2(1, -1)) tileContainer[i]->ChangeTileID(CellID::OC_NW);
			else if (floorResultDiagonal == Vector2(-1, -1)) tileContainer[i]->ChangeTileID(CellID::OC_NE);
			else if (floorResultDiagonal == Vector2(-1, 1)) tileContainer[i]->ChangeTileID(CellID::OC_SE);
			else if (floorResultDiagonal == Vector2(1, 1)) tileContainer[i]->ChangeTileID(CellID::OC_SW);

			break;
		default:
			tileContainer[i]->ChangeTileID(CellID::N);

			break;
		}


		tileContainer[i]->UpdateDebugRender();
	}





}

bool CWorld_Editable::IsFloorAdjacent(Vector2 Position)
{
	if (Position.x > 1 && Position.y > 1 && Position.x < mapScale - 1 && Position.y < mapScale - 1)
	{
		return (tileData[GridToIndex(Position + Vector2(1, 0))].id == 1 ||
			tileData[GridToIndex(Position + Vector2(-1, 0))].id == 1 ||
			tileData[GridToIndex(Position + Vector2(0, 1))].id == 1 ||
			tileData[GridToIndex(Position + Vector2(0, -1))].id == 1 ||

			tileData[GridToIndex(Position + Vector2(1, 1))].id == 1 ||
			tileData[GridToIndex(Position + Vector2(-1, -1))].id == 1 ||
			tileData[GridToIndex(Position + Vector2(1, -1))].id == 1 ||
			tileData[GridToIndex(Position + Vector2(-1, 1))].id == 1);
	}
	else return false;
}


int CWorld_Editable::GetTotalAdjacentsOfType(Vector2 Pos, CellType AdjacentType)
{
	int Total = 0;
	if (IsTile(Pos + Vector2(1, 0), AdjacentType)) Total++;
	if (IsTile(Pos + Vector2(-1, 0), AdjacentType)) Total++;
	if (IsTile(Pos + Vector2(0, -1), AdjacentType)) Total++;
	if (IsTile(Pos + Vector2(0, 1), AdjacentType)) Total++;
	return Total;
}

Vector2 CWorld_Editable::FindAdjacents(Vector2 Pos, CellType ID)
{

	int X;
	int Y;
	if (tileData[GridToIndex(Pos + Vector2(1, 0))].type == ID)
	{
		X = 1;
		if (tileData[GridToIndex(Pos + Vector2(-1, 0))].type == ID) X = 2;
	}
	else if (tileData[GridToIndex(Pos + Vector2(-1, 0))].type == ID)
	{
		X = -1;
	}
	else
		X = 0;

	if (tileData[GridToIndex(Pos + Vector2(0, 1))].type == ID)
	{
		Y = 1;
		if (tileData[GridToIndex(Pos + Vector2(0, -1))].type == ID) Y = 2;
	}
	else if (tileData[GridToIndex(Pos + Vector2(0, -1))].type == ID)
	{
		Y = -1;
	}
	else Y = 0;




	return Vector2((float)X, (float)Y);
}

Vector2 CWorld_Editable::FindAdjacentEdges(Vector2 Pos)
{


	int X;
	int Y;
	CellType cachedTypePosX = tileData[GridToIndex(Pos + Vector2(1, 0))].type;
	CellType cachedTypeNegX = tileData[GridToIndex(Pos + Vector2(-1, 0))].type;

	CellType cachedTypePosY = tileData[GridToIndex(Pos + Vector2(0, 1))].type;
	CellType cachedTypeNegY = tileData[GridToIndex(Pos + Vector2(0, -1))].type;


	if (cachedTypePosX == CellType::Edge || cachedTypePosX == CellType::InnerCorner || cachedTypePosX == CellType::OuterCorner)
	{
		X = 1;
		
		if (cachedTypeNegX == CellType::Edge || cachedTypeNegX == CellType::InnerCorner || cachedTypeNegX == CellType::OuterCorner)
			X = 2;
	}
	else if (cachedTypeNegX == CellType::Edge || cachedTypeNegX == CellType::InnerCorner || cachedTypeNegX == CellType::OuterCorner)
	{
		X = -1;
	}
	else
		X = 0;

	if (cachedTypePosY == CellType::Edge || cachedTypePosY == CellType::InnerCorner || cachedTypePosY == CellType::OuterCorner)
	{
		Y = 1;
		if (cachedTypeNegY == CellType::Edge || cachedTypeNegY == CellType::InnerCorner || cachedTypeNegY == CellType::OuterCorner)
			Y = 2;
	}
	else if (cachedTypeNegY == CellType::Edge || cachedTypeNegY == CellType::InnerCorner || cachedTypeNegY == CellType::OuterCorner)
	{
		Y = -1;
	}
	else Y = 0;



	return Vector2((float)X, (float)Y);
}

Vector2 CWorld_Editable::FindFloorAdjacentDiagonal(Vector2 Position)
{
	if (IsTile(Position + Vector2(1, 1), CellType::Floor)) return Vector2(1, 1);
	else if (IsTile(Position + Vector2(-1, -1), CellType::Floor)) return Vector2(-1, -1);
	else if (IsTile(Position + Vector2(-1, 1), CellType::Floor)) return Vector2(-1, 1);
	else if (IsTile(Position + Vector2(1, -1), CellType::Floor)) return Vector2(1, -1);
	else return Vector2(0, 0);
}

bool CWorld_Editable::SetCorner(Vector2 Position)
{
	if (GetTotalAdjacentsOfType(Position, CellType::Edge) <= 2)
	{
		std::vector<CellType> list;
		list.push_back(CellType::Edge);
		list.push_back(CellType::InnerCorner);
		list.push_back(CellType::OuterCorner);

		if (IsEdge(Position + Vector2(1, 0)) && IsEdge(Position + Vector2(0, -1)))
		{

			if (IsTile(Position + Vector2(1, -1), CellType::Floor))
			{
				tileData[GridToIndex(Position)].type = CellType::OuterCorner;
			}
			else if (IsTile(Position + Vector2(-1, 1), CellType::Floor))
			{
				tileData[GridToIndex(Position)].type = CellType::InnerCorner;
			}
		}
		if (IsEdge(Position + Vector2(1, 0)) && IsEdge(Position + Vector2(0, 1)))
		{

			if (IsTile(Position + Vector2(1, 1), CellType::Floor))
			{
				tileData[GridToIndex(Position)].type = CellType::OuterCorner;
			}
			else if (IsTile(Position + Vector2(-1, -1), CellType::Floor))
			{
				tileData[GridToIndex(Position)].type = CellType::InnerCorner;
			}
		}
		if (IsEdge(Position + Vector2(-1, 0)) && IsEdge(Position + Vector2(0, -1)))
		{

			if (IsTile(Position + Vector2(-1, -1), CellType::Floor))
			{
				tileData[GridToIndex(Position)].type = CellType::OuterCorner;
			}
			else if (IsTile(Position + Vector2(1, 1), CellType::Floor))
			{
				tileData[GridToIndex(Position)].type = CellType::InnerCorner;
			}
		}
		if (IsEdge(Position + Vector2(-1, 0)) && IsEdge(Position + Vector2(0, 1)))
		{

			if (IsTile(Position + Vector2(-1, 1), CellType::Floor))
			{
				tileData[GridToIndex(Position)].type = CellType::OuterCorner;
			}
			else if (IsTile(Position + Vector2(1, -1), CellType::Floor))
			{
				tileData[GridToIndex(Position)].type = CellType::InnerCorner;
			}
		}
	}

	return false;
}
