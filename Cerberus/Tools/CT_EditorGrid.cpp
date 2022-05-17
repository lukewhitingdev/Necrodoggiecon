#include "CT_EditorGrid.h"
#include "Cerberus\Core\Components\CSpriteComponent.h"
#include "Cerberus\Core\Environment/CGridCursor.h"
#include "Cerberus/Core/Components/CCameraComponent.h"

CT_EditorGrid::CT_EditorGrid()
{
	gridSprite = AddComponent<CSpriteComponent>();
	cursorEntity = nullptr;
	
}

void CT_EditorGrid::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

}

void CT_EditorGrid::SetupGrid(CCameraComponent* cam)
{
	
	//Instantiate the grid cursor
	CGridCursor* gridCursor = Engine::CreateEntity<CGridCursor>();
	

	//Setup the editor grid visuals
	gridSprite->LoadTexture("Resources/Tiles/GridCell.dds");
	gridSprite->SetRenderRect(XMUINT2(tileScale * mapScale, tileScale * mapScale));
	gridSprite->SetSpriteSize(XMUINT2(tileScale * mapScale, tileScale * mapScale));
	gridSprite->SetTextureOffset(XMFLOAT2(0, 0));

	Vector3 tempPos = Vector3(31 * tileScale, 31 * tileScale, 0);
	

	//tempPos += Vector3(0, 32 * tileScale, 0);

	SetPosition(tempPos);
	SetScale(Vector3(2, 2, 2));
	

}

CT_EditorGrid::~CT_EditorGrid()
{
	Engine::DestroyEntity(cursorEntity);

}

