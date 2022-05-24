#include "CWorld_Edit.h"
#include "Dependencies/NlohmannJson/json.hpp"
#include "Tools/CT_EditorMain.h"
#include "Cerberus\Tools\CT_EditorEntity.h"
#include <iostream>
#include <fstream>


/*
CellData CWorld_Editable::tileData[mapScale * mapScale];
EditOperationMode CWorld_Editable::operationType = EditOperationMode::None;
Vector2 CWorld_Editable::editOrigin = Vector2(0, 0);
bool CWorld_Editable::selectedCell = false;
bool CWorld_Editable::isQueueLocked = false;
*/


void CWorld_Editable::LoadWorld(int Slot)
{
	totalEnemyEntities = 0;
	totalPropEntities = 0;

	std::string fileName = "Resources/Levels/Level_" + std::to_string(Slot);
	fileName += ".json";


	mapSlot = Slot;

	std::ifstream file(fileName);
	if (file.is_open())
	{
		json storedFile;

		file >> storedFile;

		if (storedFile["MapScale"] != mapScale)
		{
			NewWorld(Slot);
		}
		else
		{
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

				CTile* Tile = nullptr;
				if (tileContainer[i] != nullptr)
				{
					Tile = tileContainer[i];
				}
				else
				{
					Tile = Engine::CreateEntity<CTile>();
				}


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

		}

		








		BuildNavigationGrid();

		GenerateTileMap();

		totalEnemyEntities = storedFile["EnemyCount"];


		for (int i = 0; i < totalEnemyEntities; i++)
		{
			int EnemyID = storedFile["Enemy"][i]["Type"];
			int EnemyX = storedFile["Enemy"][i]["Position"]["X"];
			int EnemyY = storedFile["Enemy"][i]["Position"]["Y"];

			float enemyHealth = storedFile["Enemy"][i]["Health"];
			float enemySpeed = storedFile["Enemy"][i]["Speed"];

			float enemyMass = storedFile["Enemy"][i]["Mass"];
			float enemyRange = storedFile["Enemy"][i]["Range"];

			float enemyRotationSpeed = storedFile["Enemy"][i]["RotationSpeed"];
			float enemyMaxSearchTime = storedFile["Enemy"][i]["MaxSearchTime"];

			
			

			
			

			
			
			

			

			CT_EditorEntity_Enemy* TempRef = Engine::CreateEntity<CT_EditorEntity_Enemy>();
			TempRef->InitialiseEntity(EnemyID);
			TempRef->SetPosition(Vector3(EnemyX, EnemyY, -1));
			editorEntityList.push_back(TempRef);

			//TempRef->SetHealth(enemyHealth);
		//	TempRef->SetSpeed(enemySpeed);
			//TempRef->SetMass(enemyMass);
			//TempRef->SetRange(enemyRange);
			//TempRef->SetRotationSpeed(enemyRotationSpeed);
			//TempRef->SetMaxSearchTime(enemyMaxSearchTime);

			if (EnemyID == 0)
			{
				int weaponIndex = storedFile["Enemy"][i]["WeaponIndex"];
				//std::string weaponName = storedFile["Enemy"][i]["WeaponType"].get<std::string>();
				//Debug::Log("WeaponName: %s", weaponName);
				TempRef->AssignWeapon((char*)"", weaponIndex);
			}


			int WaypointList = storedFile["Enemy"][i]["WaypointList"];
			for (int y = 0; y < WaypointList; y++)
			{
				int WaypointX = storedFile["Enemy"][i]["Waypoints"][y]["X"];
				int WaypointY = storedFile["Enemy"][i]["Waypoints"][y]["Y"];
				CT_EditorEntity_Waypoint* TempWaypoint = TempRef->AddWaypoint(Vector2(WaypointX, WaypointY));
				editorEntityList.push_back(TempWaypoint);

			}
			TempRef->ToggleWaypoints(false);



		}



		playerStartEntity = Engine::CreateEntity<CT_EditorEntity_PlayerStart>();
		editorEntityList.push_back(playerStartEntity);
		int StartX = storedFile["PlayerStart"]["X"];
		int StartY = storedFile["PlayerStart"]["Y"];
		playerStartEntity->SetPosition((Vector3(StartX, StartY, 0) * (tileScale * tileScaleMultiplier)) + Vector3(0,0,-1));
		

	}


	

	

	
}

void CWorld_Editable::UnloadWorld()
{
	for (int i = 0; i < editorEntityList.size(); i++)
	{
		Engine::DestroyEntity(editorEntityList[i]);
	}

	delete(editorViewport);
}
 void CWorld_Editable::SetupWorld()
{
	 editorViewport = new CT_EditorMain();

	
}



void CWorld_Editable::SaveWorld(int Slot)
{
	UNREFERENCED_PARAMETER(Slot);
	std::string fileName = "Resources/Levels/Level_" + std::to_string(Slot);
	fileName += ".json";

	std::ifstream file(fileName);


	json SaveData;

	std::vector<std::string> MapData;

	GenerateTileMap();


	for (int i = 0; i < mapScale * mapScale; i++)
	{
		MapData.push_back(std::to_string(tileContainer[i]->GetTileID()));
	}

	SaveData["MapScale"] = mapScale;
	SaveData["TileData"] = MapData;
	SaveData["EnemyCount"] = totalEnemyEntities;

	std::vector<CT_EditorEntity_Enemy*> EnemyList;
	std::vector<CT_EditorEntity_Waypoint*> WaypointList;
	

	for (int i = 0; i < editorEntityList.size(); i++)
	{
		switch (editorEntityList[i]->GetType())
		{
		case EditorEntityType::Enemy:
		
			EnemyList.push_back(static_cast<CT_EditorEntity_Enemy*>(editorEntityList[i]));
			break;
		case EditorEntityType::Waypoint:

			WaypointList.push_back(static_cast<CT_EditorEntity_Waypoint*>(editorEntityList[i]));
			break;
		}
	}

	for (int i = 0; i < EnemyList.size(); i++)
	{
		if (EnemyList[i] != nullptr)
		{
			switch (EnemyList[i]->GetType())
			{
			case EditorEntityType::Enemy:
				CT_EditorEntity_Enemy* TempEnemy = EnemyList[i];
				SaveData["Enemy"][i]["Type"] = TempEnemy->GetSlot();

				SaveData["Enemy"][i]["Position"]["X"] = TempEnemy->GetPosition().x;
				SaveData["Enemy"][i]["Position"]["Y"] = TempEnemy->GetPosition().y;
				if (TempEnemy->GetSlot() == 0)
				{
					std::string weaponName = TempEnemy->GetWeaponName();
					SaveData["Enemy"][i]["WeaponType"] = weaponName;
					SaveData["Enemy"][i]["WeaponIndex"] = TempEnemy->GetAssignedWeapon();
				}
				
			
				SaveData["Enemy"][i]["WaypointList"] = TempEnemy->Waypoints.size();
				for (int y = 0; y < TempEnemy->Waypoints.size(); y++)
				{
					SaveData["Enemy"][i]["Waypoints"][y]["X"] = TempEnemy->Waypoints[y]->gridPos.x;
					SaveData["Enemy"][i]["Waypoints"][y]["Y"] = TempEnemy->Waypoints[y]->gridPos.y;
				}

				SaveData["Enemy"][i]["Health"] = TempEnemy->GetHealth();
				SaveData["Enemy"][i]["Speed"] = TempEnemy->GetSpeed();

				SaveData["Enemy"][i]["Mass"] = TempEnemy->GetMass();
				SaveData["Enemy"][i]["Range"] = TempEnemy->GetRange();

				SaveData["Enemy"][i]["RotationSpeed"] = TempEnemy->GetRotationSpeed();
				SaveData["Enemy"][i]["MaxSearchTime"] = TempEnemy->GetMaxSearchTime();


				break;
			}
		}
		
	}

	int StartX = playerStartEntity->GetPosition().x / (tileScale * tileScaleMultiplier);
	int StartY = playerStartEntity->GetPosition().y / (tileScale * tileScaleMultiplier);
	SaveData["PlayerStart"]["X"] = StartX;
	SaveData["PlayerStart"]["Y"] = StartY;
	

	std::ofstream o(fileName);
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
		tileData[i].type = CellType::Empty;

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
	case EditOperationMode::EnemyEntity:
		Debug::Log("OperationMode: Enemy Placement");
		break;
	case EditOperationMode::WeaponHolder:
		Debug::Log("OperationMode: Weapon Placement");
		break;
	}
}

void CWorld_Editable::QueueCell(Vector2 Cell)
{
	//operationType == EditOperationMode::Additive_Single || operationType == EditOperationMode::Subtractive_Single || operationType == EditOperationMode::EnemyEntity || operationType == EditOperationMode::Waypoints ||
	if (operationType != EditOperationMode::Additive && operationType != EditOperationMode::Subtractive)
	{
		editOrigin = Cell;
		PerformOperation(editOrigin, Cell);
	}
	else if (operationType != EditOperationMode::None)
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
	case EditOperationMode::EnemyEntity:
		AddEditorEntity_EnemyCharacter(A, selectedEntityID);
		break;
	case EditOperationMode::Waypoints:
		AddEditorEntity_Waypoint(A);
		break;
	case EditOperationMode::WeaponHolder:
		AddEditorEntity_WeaponHolder(A);
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


void CWorld_Editable::ToggleDebugMode(bool isDebug)
{
	for (int i = 0; i < mapScale * mapScale; i++)
	{
		tileContainer[i]->SetDebugMode(isDebug);
	}
}

void CWorld_Editable::UpdateEditorViewport()
{
	if (editorViewport) editorViewport->RenderWindows();
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

EditorEntityType CWorld_Editable::GetInspectedItemType()
{
	if (inspectedEntity != nullptr)
	{
		return inspectedEntity->GetType();
	}
	else return EditorEntityType::None;
}

void CWorld_Editable::ShouldInspectEntity(Vector2 MousePos)
{


	inspectedEntity = nullptr;

	for (int i = 0; i < editorEntityList.size(); i++)
	{
	
		Vector3 Pos = Vector3(MousePos.x, MousePos.y, 0) * (tileScale * tileScaleMultiplier);
		Pos.z = -1;
		Vector3 EPos = editorEntityList[i]->GetPosition();

		Debug::Log("Entity Location: [%f | %f] vs Mouse Location: [%f | %f]",EPos.x, EPos.y, Pos.x, Pos.y );
		Debug::Log("Distance: %f", Pos.DistanceTo(EPos));
		if (Pos.DistanceTo(editorEntityList[i]->GetPosition()) <= 64)
		{
			Debug::Log("Entity Located");
			inspectedEntity = editorEntityList[i];
		
			
		}
		
	}
	


}

void CWorld_Editable::MoveSelectedEntity(Vector3 Position)
{


	if (inspectedEntity != nullptr) 
	{
		Vector3 CurPos = inspectedEntity->GetPosition() / (tileScale * tileScaleMultiplier);

		Vector2 Pos2d = Vector2(Position.x, Position.y);
		Vector3 NewPos = Position * (tileScale * tileScaleMultiplier);
		NewPos.z = -1;
		if (tileContainer[GridToIndex(Pos2d)]->IsWalkable())
		{
			inspectedEntity->SetPosition(NewPos);
		}

		if (!tileContainer[GridToIndex(Vector2(CurPos.x, CurPos.y))]->IsWalkable())
		{
			Vector2 Pos2d = Vector2(Position.x, Position.y);
			Vector3 NewPos = Position * (tileScale * tileScaleMultiplier);
			NewPos.z = -1;
			if (tileContainer[GridToIndex(Pos2d)]->IsWalkable())
			{
				inspectedEntity->SetPosition(NewPos);
			}
		}




	}
	
}

void CWorld_Editable::RemoveSelectedEntity()
{
	if (inspectedEntity != nullptr && inspectedEntity->GetType() != EditorEntityType::Flag)
	{
		for (int i = 0; i < editorEntityList.size(); i++)
		{
			if (editorEntityList[i] == inspectedEntity)
			{
				editorEntityList.erase(editorEntityList.begin() + i);

				Engine::DestroyEntity(inspectedEntity);

				totalEnemyEntities--;
				break;
			}
		}
	}
	

}


///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////LOOKUP DATA FOR ADDING ENTITIES////////////////
///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

void CWorld_Editable::AddEditorEntity_EnemyCharacter(Vector2 Position, int Slot)
{
	Vector3 NewPos = Vector3(Position.x, Position.y, 0) * (tileScale * tileScaleMultiplier);
	NewPos.z = -1;
	if (tileContainer[GridToIndex(Position)]->IsWalkable())
	{
		CT_EditorEntity_Enemy* TempRef = Engine::CreateEntity<CT_EditorEntity_Enemy>();
		TempRef->InitialiseEntity(Slot);
		TempRef->SetPosition(NewPos);
		editorEntityList.push_back(TempRef);
		totalEnemyEntities++;
	
	}
	
}

void CWorld_Editable::AddEditorEntity_Decoration(Vector2 Position, int Slot)
{

}

void CWorld_Editable::AddEditorEntity_Waypoint(Vector2 Position)
{
	if (tileContainer[GridToIndex(Position)]->IsWalkable())
	{
		editorEntityList.push_back(GetInspectedItem_Enemy()->AddWaypoint(Position));
	}
}

void CWorld_Editable::AddEditorEntity_WeaponHolder(Vector2 Position)
{
	Vector3 NewPos = Vector3(Position.x, Position.y, 0) * (tileScale * tileScaleMultiplier);
	NewPos.z = -1;
	if (tileContainer[GridToIndex(Position)]->IsWalkable())
	{
		CT_EditorEntity_WeaponHolder* TempRef = Engine::CreateEntity<CT_EditorEntity_WeaponHolder>();
		TempRef->SetPosition(NewPos);
		
		editorEntityList.push_back(TempRef);
		

	}
}
