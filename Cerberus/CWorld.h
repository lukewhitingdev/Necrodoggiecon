#pragma once

#include <string>
#include <vector>
#include "CTile.h"
#include "CWorldData.h"
#include "WorldConstants.h"

#include "Libraries/json.hpp"

using json = nlohmann::json;





class CWorld
{

public:
	CWorld();

	CWorld(int WorldSlot);

	void LoadWorld(int Slot);

	void ReloadWorld();

	void UnloadWorld();

	//A List of all tiles in the scene
	//std::vector<Tile*> tileList;


	
	


protected:

	void SetWorldSize(Vector3 Scale);





protected:

	void ReadSceneJSON(int Slot);
	void ReadEntityJSON(int Slot);



	
	//std::map<Vector3, CTile*> tileContainer;

	CTile* tileContainer[mapScale * mapScale];

	//This function should only be used when Loading / Reloading the scene.
	//void LoadEntity(CT_EntityData EntityData);


	//This is a list of entities loaded in with the level data. This should not be touched outside of Loading / Reloading
	//std::vector<CT_EntityData> storedEntities;


	//List of entities spawned in by this class, used for deconstruction.
	//std::vector<CEntity> entityList;


protected:

	Vector3 IndexToGrid(int ID);
	int GridToIndex(Vector2 Position);



};


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//						WORLD FOR EDITOR
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////




class CWorld_Editable : public CWorld
{


public:




	//Save the current tile data to a file
	void SaveWorld(int Slot);
	//Run edit operations currently inside of the function. Automatically save afterwards.
	void EditWorld(int Slot);

	void NewWorld(int Slot);

	void ClearSpace();


	//Sets space to be unwalkable
	void AdditiveBox(Vector2 A, Vector2 B);
	//Sets space to be walkable
	void SubtractiveBox(Vector2 A, Vector2 B);



	//Sets space to be unwalkable
	void AdditiveBox_Scale(Vector2 A, Vector2 B);
	//Sets space to be walkable
	void SubtractiveBox_Scale(Vector2 A, Vector2 B);


private:

	void BoxOperation(Vector2 A, Vector2 B, int TileID);


	void GenerateTileMap();

	void RefreshTileMapRegion(Vector2 A, Vector2 B);





	CTile* tileData[mapScale * mapScale];

	CellType CellList[mapScale * mapScale];


	//Is the selected tile adjacent to a walkable tile
	bool IsFloorAdjacent(Vector2 Position);



	bool IsTile(Vector2 Position, CellType Type)
	{
		return CellList[GridToIndex(Position)] == Type;
	}

	



	Vector2 FindAdjacents(Vector2 Pos, CellType ID);
	

	Vector2 FindFloorAdjacentDiagonal(Vector2 Position)
	{

		if (IsTile(Position + Vector2(1,1), CellType::Floor)) return Vector2(1, 1);
		else if (IsTile(Position + Vector2(-1, -1), CellType::Floor)) return Vector2(-1, -1);
		else if (IsTile(Position + Vector2(-1, 1), CellType::Floor)) return Vector2(-1, 1);
		else if (IsTile(Position + Vector2(1, -1), CellType::Floor)) return Vector2(1, -1);
		else return Vector2(0, 0);
	}

	bool SetCorner(Vector2 Position)
	{

		
		if (IsTile(Position, CellType::Edge))
		{
			if (IsTile(Position + Vector2(1,0), CellType::Edge) && IsTile(Position + Vector2(0, -1), CellType::Edge))
			{

				if (IsTile(Position + Vector2(1,-1), CellType::Floor))
				{
					CellList[GridToIndex(Position)] = CellType::OuterCorner;
				}
				


			}
			if (IsTile(Position + Vector2(1, 0), CellType::Edge) && IsTile(Position + Vector2(0, 1), CellType::Edge))
			{

				if (IsTile(Position + Vector2(1, 1), CellType::Floor))
				{
					CellList[GridToIndex(Position)] = CellType::OuterCorner;
				}



			}
			if (IsTile(Position + Vector2(-1, 0), CellType::Edge) && IsTile(Position + Vector2(0, -1), CellType::Edge))
			{

				if (IsTile(Position + Vector2(-1, -1), CellType::Floor))
				{
					CellList[GridToIndex(Position)] = CellType::OuterCorner;
				}



			}
			if (IsTile(Position + Vector2(-1, 0), CellType::Edge) && IsTile(Position + Vector2(0, 1), CellType::Edge))
			{

				if (IsTile(Position + Vector2(-1, 1), CellType::Floor))
				{
					CellList[GridToIndex(Position)] = CellType::OuterCorner;
				}



			}
		}

		return false;

	}
	

};

