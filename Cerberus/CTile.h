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


	

protected: 

	//Returns the tile's type, whether it be a walkable floor, a wall or a door.
	TileType GetTileType() { return tileStatus; }


private: 

	void SetRenderData(int X, int Y);


	TileType tileStatus;

	int tileID;






	
};

