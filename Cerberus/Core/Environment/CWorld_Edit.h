#pragma once
#include "CWorld.h"
#include "CT_EditorEntity.h"


struct CellData
{
	int id;
	CellType type;
};

enum class EditOperationMode
{
	None, Additive, Subtractive, Additive_Single, Subtractive_Single,Move_Entity ,EnemyEntity, Waypoints
};

struct PropData
{
	std::string propName;
	Vector2 CollisionData;
	Vector2 AtlasSize;
};

class CWorld_Editable : public CWorld
{


public:



	EditOperationMode GetOperationMode() { return operationType; }

	//Set the current operation mode
	 void SetOperationMode(EditOperationMode mode);
	 void SetEntityID(int ID) { SelectedEntityID = ID; }

	//Adds a cell to the Queue, once the queue is full (2 Cells) the grid will perform a edit operation;
	 void QueueCell(Vector2 Cell);

	//Sets the lock-State to the input parameter
	 void ToggleCellQueueLock(bool setLock) { isQueueLocked = setLock; }

	//Clears the Cell edit queue
	 void ClearQueue();

	 void PerformOperation(Vector2 A, Vector2 B);

	//Public wrapper for clear space, clears the queue.
	 void PerformOperation_ClearSpace();

	//Loads the world and initialises TileData
	 virtual void LoadWorld(int Slot) override;
	 virtual void UnloadWorld() override;
	 virtual void SetupWorld();

	//Save the current tile data to a file
	 void SaveWorld(int Slot);
	//Run edit operations currently inside of the function. Automatically save afterwards.
	 void EditWorld(int Slot);

	//Initialises the tileset to empty
	 void NewWorld(int Slot);


	 void ToggleDebugMode(bool isDebug);

	 void UpdateEditorViewport();

	 void AddEditorEntity_Prop(int Slot);

	

	 void AddEditorEntity_ItemHolder(int Slot);

	 
	 EditorEntityType GetInspectedItemType();
	 CT_EditorEntity* GetInspectedItem_Standard() { return InspectedEntity; }
	 class CT_EditorEntity_Enemy* GetInspectedItem_Enemy() { return static_cast<CT_EditorEntity_Enemy*>(InspectedEntity); }
	 CT_EditorEntity_Waypoint* GetInspectedItem_Waypoint() { return static_cast<CT_EditorEntity_Waypoint*>(InspectedEntity); }

	
	void ShouldInspectEntity(Vector2 MousePos);

	void MoveSelectedEntity(Vector3 Position);

	void RemoveSelectedEntity();
protected:



	//Wrapper function for BoxOperation, Sets space to be unwalkable
	 void AdditiveBox(Vector2 A, Vector2 B);

	//Wrapper function for BoxOperation, Sets space to be walkable
	 void SubtractiveBox(Vector2 A, Vector2 B);

	//Wrapper function for BoxOperation, Sets space to be unwalkable
	 void AdditiveBox_Scale(Vector2 A, Vector2 B);

	//Wrapper function for BoxOperation, Sets space to be walkable
	 void SubtractiveBox_Scale(Vector2 A, Vector2 B);

	//Clears the grid and sets all to empty
	 void ClearSpace();

	 void Additive_Cell(Vector2 A);

	 void Subtractive_Cell(Vector2 A);

	 //Add Enemy enetity to the map
	 void AddEditorEntity_EnemyCharacter(Vector2 Position, int Slot);

	 void AddEditorEntity_Decoration(Vector2 Position, int Slot);

	 void AddEditorEntity_Waypoint(Vector2 Position);


	 void GeneratePropList();

private:

	//Performs an operation on the grid, drawing a retangular shape based on the two provided coordinates.
	 void BoxOperation(Vector2 A, Vector2 B, int TileID);

	//Generates the grid based on the current tile data state.
	 void GenerateTileMap();

	//Sets any corner that qualifies as an edge to an Edge
	 bool SetCorner(Vector2 Position);

	





	 CellData tileData[mapScale * mapScale];

	//CellType CellList[mapScale * mapScale];


	//Is the selected tile adjacent to a walkable tile
	 bool IsFloorAdjacent(Vector2 Position);


	//Is the Tile at provided position equal to the provided Type
	 bool IsTile(Vector2 Position, CellType Type)
	{
		return tileData[GridToIndex(Position)].type == Type;
	}

	// the Tile at the provided position the equivalent to wall. (Edge/InnerCorner/OuterCorner)
	 bool IsEdge(Vector2 Pos)
	{
		return (tileData[GridToIndex(Pos)].type == CellType::Edge || tileData[GridToIndex(Pos)].type == CellType::OuterCorner || tileData[GridToIndex(Pos)].type == CellType::InnerCorner);
	}

	//Returns total amount of the given type of tile adjacent to the given tile.
	 int GetTotalAdjacentsOfType(Vector2 Pos, CellType AdjacentType);


	//Gets the direction of adjacent tiles that match the given type. 
	// 2 = Both sides
	// 1 = positive direction
	// -1 = negative direction
	 Vector2 FindAdjacents(Vector2 Pos, CellType ID);

	//Same as standard version but only returns the results for adjacent walls
	 Vector2 FindAdjacentEdges(Vector2 Pos);

	//Gets adjacent diagonal tiles
	//Only only returns the first result
	 Vector2 FindFloorAdjacentDiagonal(Vector2 Position);

	

private:


	//Current edit mode
	 EditOperationMode operationType;

	//Cached position for the current edit operation
	 Vector2 editOrigin;

	 //The slot that the current map is tied to.
	 int MapSlot;

	//Whether or not an operation is taking place
	 bool selectedCell;

	//Whether or not any edit operations can be performed
	 bool isQueueLocked;

	 //main editor viewport
	 class CT_EditorMain* EditorViewport;

	 //The ID of the selected entity brush, used to place entities from the content panel
	 int SelectedEntityID;

	 //The entity currently being inspected
	 CT_EditorEntity* InspectedEntity;

	 //Total number of enemy entnties used for saving
	 int TotalEnemyEntities;
	 //Total number of enemy entities used for saving
	 int TotalPropEntities;


	 //Full list of all editor entities
	 std::vector<class CT_EditorEntity*> EditorEntityList;

};

