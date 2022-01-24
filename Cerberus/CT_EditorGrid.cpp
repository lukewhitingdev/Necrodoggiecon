#include "CT_EditorGrid.h"
#include "CSpriteComponent.h"
#include "CGridCursor.h"

CT_EditorGrid::CT_EditorGrid()
{
	GridSprite = AddComponent<CSpriteComponent>();
	//ActiveCellSprite = AddComponent<CSpriteComponent>();
}

void CT_EditorGrid::Update(float deltaTime)
{


}

void CT_EditorGrid::SetupGrid()
{
	
	
	
	CGridCursor* GridCursor = Engine::CreateEntity<CGridCursor>();

	GridSprite->LoadTexture("Resources\\Tiles\\GridCell.dds");

	GridSprite->SetRenderRect(XMUINT2(tileScale * mapScale, tileScale * mapScale));
	GridSprite->SetSpriteSize(XMUINT2(tileScale * mapScale, tileScale * mapScale));
	GridSprite->SetTextureOffset(XMFLOAT2(0, 0));

	Vector3 tempPos = Vector3(31 * tileScale, 31 * tileScale, 0);
	

	//tempPos += Vector3(0, 32 * tileScale, 0);

	SetPosition(tempPos);
	SetScale(Vector3(2, 2, 2));
	

}

void CT_EditorGrid::SetCursorPosition(Vector2 Position)
{
	//Position /= mapScale;
	
	//ActiveCellSprite->SetPosition(Vector3(Inputs::InputManager::mousePos.x - Engine::windowWidth * 0.5f, -Inputs::InputManager::mousePos.y + Engine::windowHeight * 0.5f, -100));

	





}
