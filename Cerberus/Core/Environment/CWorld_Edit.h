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

	//Set the current operation mode
	static void SetOperationMode(EditOperationMode mode);

	//Adds a cell to the Queue, once the queue is full (2 Cells) the grid will perform a edit operation;
	static void QueueCell(Vector2 Cell);

	//Sets the lock-State to the input parameter
	static void ToggleCellQueueLock(bool setLock) { isQueueLocked = setLock; }

	//Clears the Cell edit queue
	static void ClearQueue();

	static void PerformOperation(Vector2 A, Vector2 B);

	//Public wrapper for clear space, clears the queue.
	static void PerformOperation_ClearSpace();

	//Loads the world and initialises TileData
	static void LoadWorld_Edit();

	//Save the current tile data to a file
	static void SaveWorld(int Slot);
	//Run edit operations currently inside of the function. Automatically save afterwards.
	static void EditWorld(int Slot);

	//Initialises the tileset to empty
	static void NewWorld(int Slot);


	static void ToggleDebugMode(bool isDebug);
	


protected:


	//Wrapper function for BoxOperation, Sets space to be unwalkable
	static void AdditiveBox(Vector2 A, Vector2 B);

	//Wrapper function for BoxOperation, Sets space to be walkable
	static void SubtractiveBox(Vector2 A, Vector2 B);

	//Wrapper function for BoxOperation, Sets space to be unwalkable
	static void AdditiveBox_Scale(Vector2 A, Vector2 B);

	//Wrapper function for BoxOperation, Sets space to be walkable
	static void SubtractiveBox_Scale(Vector2 A, Vector2 B);

	//Clears the grid and sets all to empty
	static void ClearSpace();


private:

	//Performs an operation on the grid, drawing a retangular shape based on the two provided coordinates.
	static void BoxOperation(Vector2 A, Vector2 B, int TileID);

	//Generates the grid based on the current tile data state.
	static void GenerateTileMap();

	//Sets any corner that qualifies as an edge to an Edge
	static bool SetCorner(Vector2 Position);

	





	static CellData tileData[mapScale * mapScale];

	//CellType CellList[mapScale * mapScale];


	//Is the selected tile adjacent to a walkable tile
	static bool IsFloorAdjacent(Vector2 Position);


	//Is the Tile at provided position equal to the provided Type
	static bool IsTile(Vector2 Position, CellType Type)
	{
		return tileData[GridToIndex(Position)].type == Type;
	}

	//Is the Tile at the provided position the equivalent to wall. (Edge/InnerCorner/OuterCorner)
	static bool IsEdge(Vector2 Pos)
	{
		return (tileData[GridToIndex(Pos)].type == CellType::Edge || tileData[GridToIndex(Pos)].type == CellType::OuterCorner || tileData[GridToIndex(Pos)].type == CellType::InnerCorner);
	}


	


	//Gets the direction of adjacent tiles that match the given type. 
	// 2 = Both sides
	// 1 = positive direction
	// -1 = negative direction
	static Vector2 FindAdjacents(Vector2 Pos, CellType ID);

	//Same as standard version but only returns the results for adjacent walls
	static Vector2 FindAdjacentEdges(Vector2 Pos);

	//Gets adjacent diagonal tiles
	//Only only returns the first result
	static Vector2 FindFloorAdjacentDiagonal(Vector2 Position);

	

private:


	//Current edit mode
	static EditOperationMode operationType;

	//Cached position for the current edit operation
	static Vector2 editOrigin;

	//Whether or not an operation is taking place
	static bool selectedCell;

	//Whether or not any edit operations can be performed
	static bool isQueueLocked;

};

