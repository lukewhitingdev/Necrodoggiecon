#pragma once

#include <string>
#include <vector>
#include "CTile.h"

#include "WorldConstants.h"

#include "Dependencies/NlohmannJson/json.hpp"

using json = nlohmann::json;





class CWorld
{

public:
	CWorld();

	

	static void LoadWorld(int Slot);

	

	
	//A List of all tiles in the scene
	//std::vector<Tile*> tileList;


	
	// TODO- Add collision collector
	static CTile* GetTileByID(int ID) { return tileContainer[ID]; }

	static std::vector<CTile*> GetAllWalkableTiles();

	static std::vector<CTile*> GetAllObstacleTiles();

	static void BuildNavigationGrid();

protected:

	




	




protected:

	



	
	//std::map<Vector3, CTile*> tileContainer;

	static CTile* tileContainer[mapScale * mapScale];


	//Function that loads entities based on slot, You can change the entities in each slot inside the cpp
	static void LoadEntity(int Slot, Vector3 Position);

	//This function should only be used when Loading / Reloading the scene.



	//This is a list of entities loaded in with the level data. This should not be touched outside of Loading / Reloading
	//std::vector<CT_EntityData> storedEntities;


	//List of entities spawned in by this class, used for deconstruction.
	static std::vector<class CEntity*> entityList;

protected:

	static Vector3 IndexToGrid(int ID);
	static int GridToIndex(Vector2 Position);

	



};




