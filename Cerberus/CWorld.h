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


	
	// TODO- Add collision collector


protected:

	void SetWorldSize(Vector3 Scale);


	void BuildNavigationGrid();

	CTile* GetTileByID(int ID) { return tileContainer[ID]; }






protected:

	



	
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




