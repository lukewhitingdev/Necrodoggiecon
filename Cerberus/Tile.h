#pragma once
#include "Vector3.h"

enum class TileType
{
	Floor,
	Wall,
	Door

};

class Tile
{


	Tile(int TileID, Vector3 Position);


public:


	void UpdateTile(int TileID);


protected: 

	//Returns the tile's type, whether it be a walkable floor, a wall or a door.
	TileType GetTileType() { return TileStatus; }


private: 

	TileType TileStatus;

	int ID;






	
};

