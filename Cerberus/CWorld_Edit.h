#pragma once
#include "CWorld.h"


struct CellData
{
	int id;
	CellType type;
};


class CWorld_Editable : public CWorld
{


public:




	//Save the current tile data to a file
	static void SaveWorld(int Slot);
	//Run edit operations currently inside of the function. Automatically save afterwards.
	static void EditWorld(int Slot);

	static void NewWorld(int Slot);

	static void ClearSpace();


	//Sets space to be unwalkable
	static void AdditiveBox(Vector2 A, Vector2 B);
	//Sets space to be walkable
	static void SubtractiveBox(Vector2 A, Vector2 B);



	//Sets space to be unwalkable
	static void AdditiveBox_Scale(Vector2 A, Vector2 B);
	//Sets space to be walkable
	static void SubtractiveBox_Scale(Vector2 A, Vector2 B);


private:

	static void BoxOperation(Vector2 A, Vector2 B, int TileID);


	static void GenerateTileMap();

	static void RefreshTileMapRegion(Vector2 A, Vector2 B);





	static CellData tileData[mapScale * mapScale];

	//CellType CellList[mapScale * mapScale];


	//Is the selected tile adjacent to a walkable tile
	static bool IsFloorAdjacent(Vector2 Position);



	static bool IsTile(Vector2 Position, CellType Type)
	{
		return tileData[GridToIndex(Position)].type == Type;
	}




	//Gets the direction of adjacent tiles that match the given type. 
	// 2 = Both sides
	// 1 = positive direction
	// -1 = negative direction
	static Vector2 FindAdjacents(Vector2 Pos, CellType ID);

	//Gets adjacent diagonal tiles
	//Only only returns the first result
	static Vector2 FindFloorAdjacentDiagonal(Vector2 Position);



	//Sets any corner that qualifies as an edge to an Edge
	static bool SetCorner(Vector2 Position);



};

