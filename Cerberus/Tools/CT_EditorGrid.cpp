/*****************************************************************//**
 * \file   CT_EditorGrid.cpp
 * \brief  Editor grid visuals, this class handles rendering for the square grid overlay that goes over the editor tilemap.
 * 
 * \author Samuel Elliot Jackson
 * \date   May 2022
 *********************************************************************/
#include "CT_EditorGrid.h"
#include "Cerberus\Core\Components\CSpriteComponent.h"
#include "Cerberus\Core\Environment/CGridCursor.h"
#include "Cerberus/Core/Components/CCameraComponent.h"

/**
 * Standard constructor for the Editor Grid.
 * 
 */
CT_EditorGrid::CT_EditorGrid()
{
	gridSprite = AddComponent<CSpriteComponent>(NAME_OF(gridSprite));
	cursorEntity = nullptr;
	
}

/**
 * Standard update function, inherited from CEntity.
 *
 * \param deltaTime Time taken betweeen frames.
 */
void CT_EditorGrid::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

}
/**
 * Sets up the grid to the correct scale.
 * 
 * \param cam
 */

void CT_EditorGrid::SetupGrid(CCameraComponent* cam)
{
	
	//Instantiate the grid cursor
	CGridCursor* gridCursor = Engine::CreateEntity<CGridCursor>();
	

	//Setup the editor grid visuals
	gridSprite->LoadTexture("Resources/Game/Tiles/GridCell.dds");
	gridSprite->SetRenderRect(XMUINT2(tileScale * mapScale, tileScale * mapScale));
	gridSprite->SetSpriteSize(XMUINT2(tileScale * mapScale, tileScale * mapScale));
	gridSprite->SetTextureOffset(XMFLOAT2(0, 0));

	Vector3 tempPos = Vector3((mapScale - 1) * tileScale, (mapScale - 1) * tileScale, -1);
	

	//tempPos += Vector3(0, 32 * tileScale, 0);

	SetPosition(tempPos);
	SetScale(Vector3(2, 2, 2));
	

}
/**
 * Default Destructor, trigers grid cursor destruction.
 * 
 */
CT_EditorGrid::~CT_EditorGrid()
{
	Engine::DestroyEntity(cursorEntity);

}

