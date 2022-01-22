#include "EditorGrid.h"
#include "CSpriteComponent.h"
#include "CGridCursor.h"

EditorGrid::EditorGrid()
{
	GridSprite = AddComponent<CSpriteComponent>();
	//ActiveCellSprite = AddComponent<CSpriteComponent>();
}

void EditorGrid::Update(float deltaTime)
{
	Vector3 MousePos = Inputs::InputManager::mousePos;
	SetCursorPosition(Vector2(MousePos.x, MousePos.y));

}

void EditorGrid::SetupGrid()
{
	
	
	
	CGridCursor* GridCursor = Engine::CreateEntity<CGridCursor>();

	GridSprite->LoadTexture("Resources\\Tiles\\GridCell.dds");

	GridSprite->SetRenderRect(XMUINT2(tileScale * mapScale, tileScale * mapScale));
	GridSprite->SetSpriteSize(XMUINT2(tileScale * mapScale, tileScale * mapScale));
	GridSprite->SetTextureOffset(XMFLOAT2(0, 0));

	Vector3 tempPos = Vector3(-33 * tileScale, -32, 0);
	

	//tempPos += Vector3(0, 32 * tileScale, 0);

	SetPosition(tempPos);
	SetScale(Vector3(2, 2, 2));
	

}

void EditorGrid::SetCursorPosition(Vector2 Position)
{
	//Position /= mapScale;
	
	//ActiveCellSprite->SetPosition(Vector3(Inputs::InputManager::mousePos.x - Engine::windowWidth * 0.5f, -Inputs::InputManager::mousePos.y + Engine::windowHeight * 0.5f, -100));

	





}
