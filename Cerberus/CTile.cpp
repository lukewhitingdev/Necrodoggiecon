#include "CTile.h"
#include "CSpriteComponent.h"


CTile::CTile()
{
	sprite = AddComponent<CSpriteComponent>();
	position = Vector3(0, 0, 0);
	scale = Vector3(0, 0, 0);
	rotation = 0.0f;
}

CTile::CTile(int ID, Vector3 Position)
{
	tileID = ID;
	SetPosition(Position);

	sprite = AddComponent<CSpriteComponent>();
	
	
}

void CTile::Update(float deltaTime)
{
}

CTile::~CTile()
{
}

void CTile::ChangeTileID(CellID TileID)
{
	tileID = static_cast<int>(TileID);

	//sprite->LoadTexture("Resources\\Tiles\\Unwalkable.dds");

	
	switch (TileID)
	{
	case CellID::N:
		SetRenderData(1,1);
		break;

		

	case CellID::F:
		SetRenderData(6, 2);
		break;

	//WALLS

	case CellID::W_N:
		SetRenderData(6,1);
		break;
	case CellID::W_E:
		SetRenderData(7,2);
		break;
	case CellID::W_S:
		SetRenderData(6,3);
		break;
	case CellID::W_W:
		SetRenderData(5,2);
		break;
	//OUTER CORNER
	case CellID::OC_NE:
		SetRenderData(7,1);
		break;
	case CellID::OC_NW:
		
		SetRenderData(5,1);
		break;
	case CellID::OC_SW:
		SetRenderData(5,3);
		break;
	case CellID::OC_SE:
		SetRenderData(7,3);
		break;
		
		//INNER CORNER

	case CellID::IC_NE:
		SetRenderData(9,0);
		break;
	case CellID::IC_NW:
		SetRenderData(8,0);
		break;
	case CellID::IC_SW:
		SetRenderData(9,3);
		break;
	case CellID::IC_SE:
		SetRenderData(8,3);
		break;
	default:
		SetRenderData(0,0);
		break;
	}


	
}

void CTile::SetRenderData(int X, int Y)
{
	sprite->LoadTexture("Resources\\Tiles\\TempTileMap.dds");
	sprite->SetRenderRect(XMUINT2(tileScale, tileScale));
	sprite->SetSpriteSize(XMUINT2(tileScale, tileScale));
	sprite->SetTextureOffset(XMFLOAT2(X * tileScale, Y * tileScale));
	
}
