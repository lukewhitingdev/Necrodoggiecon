#include "EditorGrid.h"
#include "CSpriteComponent.h"

EditorGrid::EditorGrid()
{
	GridSprite = AddComponent<CSpriteComponent>();
}

void EditorGrid::Update(float deltaTime)
{
}

void EditorGrid::SetupGrid()
{

	GridSprite->LoadTexture("Resources\\Tiles\\GridCell.dds");
	GridSprite->SetRenderRect(XMUINT2(tileScale * mapScale, tileScale * mapScale));
	GridSprite->SetSpriteSize(XMUINT2(tileScale * mapScale, tileScale * mapScale));


	Vector3 tempPos = Vector3(-33 * tileScale, -32, 0);
	

	//tempPos += Vector3(0, 32 * tileScale, 0);

	SetPosition(tempPos);
	SetScale(Vector3(2, 2, 2));
	

}
