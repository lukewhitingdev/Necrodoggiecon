#pragma once

#include <string>
#include <vector>
#include "CTile.h"
#include "CWorldData.h"
#include "DataStorage.h"

#include "Libraries/json.hpp"

using json = nlohmann::json;


#define tileScale 16
#define	mapScale 256

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

	CTile* tileConainer[mapScale][mapScale];

	//This function should only be used when Loading / Reloading the scene.
	void LoadEntity(CT_EntityData EntityData);


	//This is a list of entities loaded in with the level data. This should not be touched outside of Loading / Reloading
	std::vector<CT_EntityData> storedEntities;


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

};

