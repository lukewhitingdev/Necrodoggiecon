#pragma once
#include "CWorld.h"
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


	Vector2 FindFloorAdjacentDiagonal(Vector2 Position);


	bool SetCorner(Vector2 Position);



};

