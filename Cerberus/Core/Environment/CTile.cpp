#include "CTile.h"
#include "CSpriteComponent.h"


CTile::CTile()
{
	sprite = AddComponent<CSpriteComponent>();
	isWalkable = false;
	navId = -1;
	tileId = -1;
	tileStatus = TileType::Floor;

}

CTile::CTile(int ID, Vector3 Position)
{
	tileId = ID;
	tileStatus = TileType::Floor;
	SetPosition(Position);

	sprite = AddComponent<CSpriteComponent>();
	
	
}

void CTile::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

CTile::~CTile()
{
}

void CTile::ChangeTileID(CellID TileID)
{
	tileId = static_cast<int>(TileID);

	//sprite->LoadTexture("Resources\\Tiles\\Unwalkable.dds");
	isWalkable = false;
	
	switch (TileID)
	{
	case CellID::N:
		SetRenderData(1,1);
		break;

		

	case CellID::F:
		SetRenderData(4, 1);
		isWalkable = true;
		break;

	//WALLS

	case CellID::W_N:
		SetRenderData(4,0);
		colComponent = new CollisionComponent("Wall");
		colComponent->SetCollider(tileScale, tileScale);
		colComponent->SetPosition(GetPosition());
		break;
	case CellID::W_E:
		SetRenderData(5,1);
		colComponent = new CollisionComponent("Wall");
		colComponent->SetCollider(tileScale, tileScale);
		colComponent->SetPosition(GetPosition());
		break;
	case CellID::W_S:
		SetRenderData(4,2);
		colComponent = new CollisionComponent("Wall");
		colComponent->SetCollider(tileScale, tileScale);
		colComponent->SetPosition(GetPosition());
		break;
	case CellID::W_W:
		SetRenderData(3,1);
		colComponent = new CollisionComponent("Wall");
		colComponent->SetCollider(tileScale, tileScale);
		colComponent->SetPosition(GetPosition());
		break;
	//OUTER CORNER
	case CellID::OC_NE:
		SetRenderData(5,0);
		colComponent = new CollisionComponent("Wall");
		colComponent->SetCollider(tileScale, tileScale);
		colComponent->SetPosition(GetPosition());
		break;
	case CellID::OC_NW:
		
		SetRenderData(3,0);
		colComponent = new CollisionComponent("Wall");
		colComponent->SetCollider(tileScale, tileScale);
		colComponent->SetPosition(GetPosition());
		break;
	case CellID::OC_SW:
		SetRenderData(3,2);
		colComponent = new CollisionComponent("Wall");
		colComponent->SetCollider(tileScale, tileScale);
		colComponent->SetPosition(GetPosition());
		break;
	case CellID::OC_SE:
		SetRenderData(5,2);
		colComponent = new CollisionComponent("Wall");
		colComponent->SetCollider(tileScale, tileScale);
		colComponent->SetPosition(GetPosition());
		break;
		
		//INNER CORNER

	case CellID::IC_NE:
		SetRenderData(7,0);
		colComponent = new CollisionComponent("Wall");
		colComponent->SetCollider(tileScale, tileScale);
		colComponent->SetPosition(GetPosition());
		break;
	case CellID::IC_NW:
		SetRenderData(6,0);
		colComponent = new CollisionComponent("Wall");
		colComponent->SetCollider(tileScale, tileScale);
		colComponent->SetPosition(GetPosition());
		break;
	case CellID::IC_SW:
		SetRenderData(7,2);
		colComponent = new CollisionComponent("Wall");
		colComponent->SetCollider(tileScale, tileScale);
		colComponent->SetPosition(GetPosition());
		break;
	case CellID::IC_SE:
		SetRenderData(6,2);
		colComponent = new CollisionComponent("Wall");
		colComponent->SetCollider(tileScale, tileScale);
		colComponent->SetPosition(GetPosition());
		break;
	default:
		SetRenderData(1,1);
		colComponent = new CollisionComponent("Wall");
		colComponent->SetCollider(tileScale, tileScale);
		colComponent->SetPosition(GetPosition());
		break;
	}


	
}



bool CTile::SetDebugMode(bool newState)
{
	
	if (debugSprite == nullptr)
	{
		debugSprite = AddComponent<CSpriteComponent>();
	}

	debugMode = newState;

	if (newState)
	{

		debugSprite->SetPosition(debugSprite->GetPosition().x, debugSprite->GetPosition().y, -100);
		debugSprite->LoadTexture("Resources\\Tiles\\DebugTexture.dds");
		debugSprite->SetRenderRect(XMUINT2(tileScale, tileScale));
		debugSprite->SetSpriteSize(XMUINT2(tileScale, tileScale));
		if (isWalkable)
		{
			debugSprite->SetTextureOffset(XMFLOAT2(float(tileScale), float(0)));
		}
		else
		{
			debugSprite->SetTextureOffset(XMFLOAT2(float(0), float(0)));
		}
	}
	else
	{
		debugSprite->SetPosition(debugSprite->GetPosition().x, debugSprite->GetPosition().y, +100);
	}

	

	return false;
}

void CTile::UpdateDebugRender()
{
	if (debugMode)
	{
		if (isWalkable)
		{
			debugSprite->SetTextureOffset(XMFLOAT2(float(tileScale), float(0)));
		}
		else
		{
			debugSprite->SetTextureOffset(XMFLOAT2(float(0), float(0)));
		}

	}
}

void CTile::SetRenderData(int X, int Y)
{
	sprite->LoadTexture("Resources\\Tiles\\TempTileMap.dds");
	sprite->SetRenderRect(XMUINT2(tileScale, tileScale));
	sprite->SetSpriteSize(XMUINT2(tileScale, tileScale));
	sprite->SetTextureOffset(XMFLOAT2(float(X * tileScale), float(Y * tileScale)));

	
	
}
