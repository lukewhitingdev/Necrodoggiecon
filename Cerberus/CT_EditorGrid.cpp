#include "CT_EditorGrid.h"
#include "CSpriteComponent.h"
#include "CGridCursor.h"

CT_EditorGrid::CT_EditorGrid()
{
	GridSprite = AddComponent<CSpriteComponent>();
	
}

void CT_EditorGrid::Update(float deltaTime)
{


}

void CT_EditorGrid::SetupGrid()
{
	
	
	//Instantiate the grid cursor
	CGridCursor* GridCursor = Engine::CreateEntity<CGridCursor>();



	//Setup the editor grid visuals
	GridSprite->LoadTexture("Resources\\Tiles\\GridCell.dds");
	GridSprite->SetRenderRect(XMUINT2(tileScale * mapScale, tileScale * mapScale));
	GridSprite->SetSpriteSize(XMUINT2(tileScale * mapScale, tileScale * mapScale));
	GridSprite->SetTextureOffset(XMFLOAT2(0, 0));

	Vector3 tempPos = Vector3(31 * tileScale, 31 * tileScale, 0);
	

	//tempPos += Vector3(0, 32 * tileScale, 0);

	SetPosition(tempPos);
	SetScale(Vector3(2, 2, 2));
	

}

