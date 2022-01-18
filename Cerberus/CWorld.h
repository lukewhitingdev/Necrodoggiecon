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

	CTile* tileContainer[mapScale][mapScale];

	//This function should only be used when Loading / Reloading the scene.
	//void LoadEntity(CT_EntityData EntityData);


	//This is a list of entities loaded in with the level data. This should not be touched outside of Loading / Reloading
	//std::vector<CT_EntityData> storedEntities;


	//List of entities spawned in by this class, used for deconstruction.
	//std::vector<CEntity> entityList;


private:

	Vector3 IDToWorldSpace(int ID);


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


	CTile* tileData[mapScale][mapScale];

	CellType CellList[mapScale][mapScale];


	bool IsFloorAdjacent(Vector2 Position)
	{
		if (Position.x > 1 && Position.y > 1 && Position.x < mapScale - 1 && Position.y < mapScale - 1)
		{
			return (tileData[(int)Position.x + 1][(int)Position.y]->GetTileID() == 1 ||
				tileData[(int)Position.x - 1][(int)Position.y]->GetTileID() == 1 ||
				tileData[(int)Position.x][(int)Position.y + 1]->GetTileID() == 1 ||
				tileData[(int)Position.x][(int)Position.y - 1]->GetTileID() == 1 ||

				tileData[(int)Position.x + 1][(int)Position.y + 1]->GetTileID() == 1 ||
				tileData[(int)Position.x - 1][(int)Position.y - 1]->GetTileID() == 1 ||
				tileData[(int)Position.x - 1][(int)Position.y + 1]->GetTileID() == 1 ||
				tileData[(int)Position.x + 1][(int)Position.y - 1]->GetTileID() == 1);
		}
		else return false;
	}
	int GetAdjacentEdges(Vector2 Position)
	{
		int x = Position.x;
		int y = Position.y;
		int Edges = 0;
		if (CellList[x + 1][y] == CellType::Edge) Edges++;
		if (CellList[x - 1][y] == CellType::Edge) Edges++;
		if (CellList[x][y + 1] == CellType::Edge) Edges++;
		if (CellList[x][y - 1] == CellType::Edge) Edges++;
		return Edges;

	}
	bool IsTile(int x, int y, CellType Type)
	{
		return CellList[x][y] == Type;
	}

	

	Vector2 FindFloorAdjacent(int x, int y)
	{
		if (IsTile(x + 1, y, CellType::Floor)) return Vector2(1, 0);
		else if (IsTile(x - 1, y, CellType::Floor)) return Vector2(-1, 0);
		else if (IsTile(x, y + 1, CellType::Floor)) return Vector2(0,1);
		else if (IsTile(x, y - 1, CellType::Floor)) return Vector2(0,-1);
		else return Vector2(0, 0);
	}
	Vector2 FindAdjacents(int x, int y, CellType ID)
	{
		if (IsTile(x + 1, y, ID)) return Vector2(1, 0);
		else if (IsTile(x - 1, y, ID)) return Vector2(-1, 0);
		else if (IsTile(x, y + 1, ID)) return Vector2(0, 1);
		else if (IsTile(x, y - 1, ID)) return Vector2(0, -1);
		else return Vector2(0, 0);
	}

	Vector2 FindFloorAdjacentDiagonal(int x, int y)
	{
		if (IsTile(x + 1, y + 1, CellType::Floor)) return Vector2(1, 1);
		else if (IsTile(x - 1, y - 1, CellType::Floor)) return Vector2(-1, -1);
		else if (IsTile(x - 1, y + 1, CellType::Floor)) return Vector2(-1, 1);
		else if (IsTile(x + 1, y - 1, CellType::Floor)) return Vector2(1, -1);
		else return Vector2(0, 0);
	}

	bool SetCorner(int x, int y)
	{
		
		if (IsTile(x,y, CellType::Edge))
		{
			if (IsTile(x + 1, y, CellType::Edge) && IsTile(x, y - 1, CellType::Edge))
			{

				if (IsTile(x + 1, y - 1, CellType::Floor))
				{
					CellList[x][y] = CellType::OuterCorner;
				}
				


			}
			if (IsTile(x + 1, y, CellType::Edge) && IsTile(x, y + 1, CellType::Edge))
			{
				if (IsTile(x + 1, y + 1, CellType::Floor))
				{
					CellList[x][y] = CellType::OuterCorner;
				}
				


			}
			if (IsTile(x - 1, y, CellType::Edge) && IsTile(x, y - 1, CellType::Edge))
			{
				if (IsTile(x - 1, y - 1, CellType::Floor))
				{
					CellList[x][y] = CellType::OuterCorner;
				}
			


			}
			if (IsTile(x - 1, y, CellType::Edge) && IsTile(x, y + 1, CellType::Edge))
			{
				if (IsTile(x - 1, y + 1, CellType::Floor))
				{
					CellList[x][y] = CellType::OuterCorner;
				}
				


			}
		}

		return false;

	}
	

};

