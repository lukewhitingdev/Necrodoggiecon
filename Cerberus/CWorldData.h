#pragma once
#include <map>
#include "Vector3.h"
#include <vector>

class Tile;

class CWorldData
{
public:

	CWorldData(std::map<Vector3, Tile*> WorldData) : tileContainer(WorldData) {  }


	std::vector<Tile&> GetWalkableTiles_InRange(int X, int Y);
	std::vector<Tile&> GetAllDoors();

	std::vector<Tile&> GetNearestDoors(float Range);






protected: 


	std::map<Vector3, Tile*> tileContainer;
	

private: 
	
	



};



class CWorldData_Editable : public CWorldData
{

	CWorldData_Editable(Vector3 Scale);


	Tile* GetTile(Vector3 Position) { if (tileContainer.find(Position) != tileContainer.end()) return tileContainer[Position];
	}



};
