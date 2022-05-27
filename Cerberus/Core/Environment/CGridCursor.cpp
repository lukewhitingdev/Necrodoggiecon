/*****************************************************************//**
 * \file   CGridCursor.cpp
 * \brief  
 * 
 * \author Samuel Elliot Jackson
 * \date   May 2022
 *********************************************************************/
#include "Cerberus\Core\Environment\CGridCursor.h"
#include "Cerberus\Core\Components\CSpriteComponent.h"
#include "Cerberus\Core\Environment\CWorld_Edit.h"
#include "Cerberus\Core\Engine.h"
#include "Cerberus\Core\Structs\CCamera.h"
#include "Cerberus\Dependencies\IMGUI\imgui.h"
#include "Cerberus\Core\Utility\CWorldManager.h"
#include <DirectXMath.h>
#include "Cerberus/Core/Utility/CameraManager/CameraManager.h"
#include "Cerberus/Core/Components/CCameraComponent.h"

/**
 * Standard constructor.
 * 
 */
CGridCursor::CGridCursor()
{
	Offset = Vector3(0, 0, 0);

	activeCellSprite = AddComponent<CSpriteComponent>(NAME_OF(activeCellSprite));
	activeCellSprite->LoadTexture("Resources/Game/Tiles/ActiveCell.dds");

	activeCellSprite->SetRenderRect(XMUINT2(tileScale, tileScale));
	activeCellSprite->SetSpriteSize(XMUINT2(tileScale, tileScale));
	activeCellSprite->SetTextureOffset(XMFLOAT2(0, 0));
	
	SetScale(2, 2, 2);

	screenMoved = false;

	cellSelected = false;

	selectedCell_1 = Vector3(0, 0, 0);


	//activeCellSprite->SetSpriteSize(XMUINT2(tileScale * 50, tileScale * 50));

	
	wasMouseReleased = true;
}

/**
 * Standard update function inherited from CEntity. This is where the majority of this class functions.
 * 
 * \param deltaTime Time taken between frames
 */
void CGridCursor::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	

	Vector3 camPos = Vector3(CameraManager::GetRenderingCamera()->GetPosition().x, CameraManager::GetRenderingCamera()->GetPosition().y, -10);

	Vector3 MousePos2 = Vector3(InputManager::mousePos.x - Engine::windowWidth * 0.5f, -InputManager::mousePos.y + Engine::windowHeight * 0.5f, -100);

	MousePos2 /= CameraManager::GetRenderingCamera()->GetZoomLevel();


	Vector3 Result = MousePos2 + camPos;
	

	int X = (int)((Result.x + ((tileScale * tileScaleMultiplier) / 2)) / (tileScale * tileScaleMultiplier));
	int Y = (int)((Result.y + ((tileScale * tileScaleMultiplier) / 2)) / (tileScale * tileScaleMultiplier));
	
	

	if (X <= 0) X = 0;
	if (Y <= 0) Y = 0;


	if (X >= mapScale) X = mapScale - 1;
	if (Y >= mapScale) Y = mapScale - 1;


	Vector3 Pos = Vector3((float)(X * ((tileScale * tileScaleMultiplier))), (float)(Y * ((tileScale * tileScaleMultiplier))), -5);
	Vector3 PreScale = Vector3((float)X, (float)Y, (float)-5);
	Vector3 UpScale = (PreScale - selectedCell_1);

	Vector2 RenderScale;


	SetPosition(Pos );

	//activeCellSprite->SetSpriteSize(XMUINT2(tileScale * mapScale, tileScale * mapScale));
	if (cellSelected)
	{
		UpScale = (PreScale - selectedCell_1);

	}
	


	if (InputManager::IsMouseButtonPressed(InputManager::LButton) && wasMouseReleased)
	{
		if (CWorldManager::GetEditorWorld()->GetOperationMode() != EditOperationMode::Move_Entity)
		{
			CWorldManager::GetEditorWorld()->QueueCell(Vector2(PreScale.x, PreScale.y));
			wasMouseReleased = false;
		}
		else
		{
			CWorldManager::GetEditorWorld()->MoveSelectedEntity(PreScale);
		}
		


	}
	else if (!wasMouseReleased && !InputManager::IsMouseButtonPressed(InputManager::LButton))
	{
		wasMouseReleased = true;
	}

	if (InputManager::IsMouseButtonPressed(InputManager::RButton))
	{
		CWorldManager::GetEditorWorld()->ShouldInspectEntity(Vector2(PreScale.x, PreScale.y));
		if (cellSelected)
		{
			CWorldManager::GetEditorWorld()->ClearQueue();
			
		

			cellSelected = false;
		}
	}

	if (InputManager::IsKeyPressed(InputManager::C))
	{
		CWorldManager::GetEditorWorld()->SetOperationMode(EditOperationMode::None);
	}
	if (InputManager::IsKeyPressed(InputManager::W))
	{
		CWorldManager::GetEditorWorld()->SetOperationMode(EditOperationMode::Move_Entity);
	}
	if (InputManager::IsKeyPressed(InputManager::Delete))
	{
		CWorldManager::GetEditorWorld()->RemoveSelectedEntity();
	}
	
	//mouseCalc. * -1;


	


	//activeCellSprite->SetSpriteSize(XMUINT2(X1, Y2));
	
	
	

	
}


