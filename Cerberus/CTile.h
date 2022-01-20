#pragma once
#include "Vector3.h"
#include "CEntity.h"

#include "WorldConstants.h"

enum class TileType
{
	Floor,
	Wall,
	Door

};

class CTile : public CEntity
{
public:
	CTile();
	CTile(int TileID, Vector3 Position);
	class CSpriteComponent* sprite = nullptr;



	virtual void Update(float deltaTime) override;
	virtual ~CTile();


	

	void ChangeTileID(CellID TileID);
	void ChangeTileID(int ID)
	{
		ChangeTileID(static_cast<CellID>(ID));
	}
	int GetTileID() { return tileID; }


	
	std::vector<CTile*> GetConnectedTiles() { return ConnectedTiles; }


	void AddConnectedTile(CTile* Tile);


	void SetNavID(int ID) { NavID = ID; }

protected: 

	//Returns the tile's type, whether it be a walkable floor, a wall or a door.
	TileType GetTileType() { return tileStatus; }


private: 


	bool isWalkable;

	void SetRenderData(int X, int Y);


	TileType tileStatus;

	int tileID;

	int NavID;

	std::vector<CTile*> ConnectedTiles;






	
};

