#pragma once
#include "CWorld.h"


struct CellData
{
	int id;
	CellType type;
};

enum class EditOperationMode
{
	None, Additive, Subtractive
};

class CWorld_Editable : public CWorld
{


public:


	static void SetOperationMode(EditOperationMode mode);

	//Adds a cell to the Queue, once the queue is full (2 Cells) the grid will perform a edit operation;
	static void QueueCell(Vector2 Cell);

	static void ToggleCellQueueLock(bool setLock) { isQueueLocked = setLock; }

	//Clears the Cell edit queue
	static void ClearQueue();

	static void PerformOperation(Vector2 A, Vector2 B);

	static void PerformOperation_ClearSpace();

	static void LoadWorld_Edit();

	//Save the current tile data to a file
	static void SaveWorld(int Slot);
	//Run edit operations currently inside of the function. Automatically save afterwards.
	static void EditWorld(int Slot);

	static void NewWorld(int Slot);

	


protected:


	//Sets space to be unwalkable
	static void AdditiveBox(Vector2 A, Vector2 B);
	//Sets space to be walkable
	static void SubtractiveBox(Vector2 A, Vector2 B);



	//Sets space to be unwalkable
	static void AdditiveBox_Scale(Vector2 A, Vector2 B);
	//Sets space to be walkable
	static void SubtractiveBox_Scale(Vector2 A, Vector2 B);

	static void ClearSpace();


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

	static bool IsEdge(Vector2 Pos)
	{
		return (tileData[GridToIndex(Pos)].type == CellType::Edge || tileData[GridToIndex(Pos)].type == CellType::OuterCorner || tileData[GridToIndex(Pos)].type == CellType::InnerCorner);
	}


	static bool IsTile(Vector2 Position, std::vector<CellType> Type);


	//Gets the direction of adjacent tiles that match the given type. 
	// 2 = Both sides
	// 1 = positive direction
	// -1 = negative direction
	static Vector2 FindAdjacents(Vector2 Pos, CellType ID);

	//Same as standard version, only this time also accepts 2 IDs
	static Vector2 FindAdjacentEdges(Vector2 Pos);

	//Gets adjacent diagonal tiles
	//Only only returns the first result
	static Vector2 FindFloorAdjacentDiagonal(Vector2 Position);



	//Sets any corner that qualifies as an edge to an Edge
	static bool SetCorner(Vector2 Position);

private:

	static EditOperationMode operationType;

	static Vector2 editOrigin;

	static bool selectedCell;

	static bool isQueueLocked;

};

