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
	int GetTileID() { return tileId; }


	
	std::vector<int> GetConnectedTiles() { return connectedTiles; }


	void AddConnectedTile(int Tile) { connectedTiles.push_back(Tile); }


	void SetNavID(int ID) { navId = ID; }

	int GetNavID() { return navId; }

	bool IsWalkable() { return isWalkable; }

protected: 

	//Returns the tile's type, whether it be a walkable floor, a wall or a door.
	TileType GetTileType() { return tileStatus; }


private: 


	bool isWalkable;

	void SetRenderData(int X, int Y);


	TileType tileStatus;

	int tileId;

	int navId;

	std::vector<int> connectedTiles;






	
};

