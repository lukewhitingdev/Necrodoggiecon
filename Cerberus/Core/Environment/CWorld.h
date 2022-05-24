#pragma once

#include <string>
#include <vector>
#include "CTile.h"

#include "Cerberus\WorldConstants.h"


#include "Necrodoggiecon/Game/AI/AlarmEnemy.h"
#include "Necrodoggiecon/Game/AI/MeleeEnemy.h"
#include "Necrodoggiecon/Game/AI/DogEnemy.h"
#include "Cerberus\Dependencies\NlohmannJson\json.hpp"

using json = nlohmann::json;

class CWorld
{

public:
	CWorld();
	CWorld(int Slot);

	

	virtual void LoadWorld(int Slot);
	 
	//Extendable function, primarily used to setup unique level specific requirements, one of these things would be the editor peripheral
	virtual void SetupWorld();

	virtual void UnloadWorld();

	

	virtual void ReloadWorld();

	

	
	//A List of all tiles in the scene
	//std::vector<Tile*> tileList;


	
	// TODO- Add collision collector
	 CTile* GetTileByID(int ID) { return tileContainer[ID]; }

	 std::vector<CTile*> GetAllWalkableTiles();

	 std::vector<CTile*> GetAllObstacleTiles();

	 void BuildNavigationGrid();

protected:

	

	virtual void LoadEntities(int Slot);



	




protected:

	

	int mapSize = mapScale * mapScale;


	
	//std::map<Vector3, CTile*> tileContainer;

	 CTile* tileContainer[mapScale * mapScale];


	//Function that loads entities based on slot, You can change the entities in each slot inside the cpp
	//static void LoadEntity(int Slot, Vector3 Position);

	//This function should only be used when Loading / Reloading the scene.



	//This is a list of entities loaded in with the level data. This should not be touched outside of Loading / Reloading
	//std::vector<CT_EntityData> storedEntities;


	//List of entities spawned in by this class, used for deconstruction.
	//static std::vector<class CEntity*> entityList;

protected:

	 Vector3 IndexToGrid(int ID);
	 int GridToIndex(Vector2 Position);

	 

	 //The slot that the current map is tied to.
	 int mapSlot;

	 std::vector<CEntity*> EntityList;


	Vector2 StartPos;



};




