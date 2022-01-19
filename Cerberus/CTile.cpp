#include "CTile.h"
#include "CSpriteComponent.h"


CTile::CTile()
{
	sprite = AddComponent<CSpriteComponent>();
	position = Vector3(0, 0, 0);
	scale = Vector3(0, 0, 0);
	rotation = 0.0f;
	tileID = -1;
	tileStatus = TileType::Floor;
}

CTile::CTile(int ID, Vector3 Position)
{
	tileID = ID;
	tileStatus = TileType::Floor;
	SetPosition(Position);

	sprite = AddComponent<CSpriteComponent>();
	
	
}

void CTile::Update(float deltaTime)
{
}

CTile::~CTile()
{
}

void CTile::ChangeTileID(int TileID)
{
	if (TileID == 0) sprite->LoadTexture("Resources\\Unwalkable.dds");
	else sprite->LoadTexture("Resources\\Walkable.dds");
}
