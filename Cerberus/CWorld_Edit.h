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





	CellData tileData[mapScale * mapScale];

	//CellType CellList[mapScale * mapScale];


	//Is the selected tile adjacent to a walkable tile
	bool IsFloorAdjacent(Vector2 Position);



	bool IsTile(Vector2 Position, CellType Type)
	{
		return tileData[GridToIndex(Position)].type == Type;
	}




	//Gets the direction of adjacent tiles that match the given type. 
	// 2 = Both sides
	// 1 = positive direction
	// -1 = negative direction
	Vector2 FindAdjacents(Vector2 Pos, CellType ID);

	//Gets adjacent diagonal tiles
	//Only only returns the first result
	Vector2 FindFloorAdjacentDiagonal(Vector2 Position);



	//Sets any corner that qualifies as an edge to an Edge
	bool SetCorner(Vector2 Position);



};

