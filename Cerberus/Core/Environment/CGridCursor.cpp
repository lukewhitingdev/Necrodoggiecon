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

CGridCursor::CGridCursor()
{
	Offset = Vector3(0, 0, 0);

	activeCellSprite = AddComponent<CSpriteComponent>();
	activeCellSprite->LoadTexture("Resources/Tiles/ActiveCell.dds");

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


void CGridCursor::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	

	Vector3 camPos = Vector3(CameraManager::GetRenderingCamera()->GetPosition().x, CameraManager::GetRenderingCamera()->GetPosition().y, -10);

	Vector3 MousePos2 = Vector3(Inputs::InputManager::mousePos.x - Engine::windowWidth * 0.5f, -Inputs::InputManager::mousePos.y + Engine::windowHeight * 0.5f, -100);

	MousePos2 /= CameraManager::GetRenderingCamera()->GetZoomLevel();


	Vector3 Result = MousePos2 + camPos;
	

	int X = (int)(Result.x / (tileScale * tileScaleMultiplier));
	int Y = (int)(Result.y / (tileScale * tileScaleMultiplier));
	


	if (X <= 0) X = 0;
	if (Y <= 0) Y = 0;


	if (X >= mapScale) X = mapScale - 1;
	if (Y >= mapScale) Y = mapScale - 1;


	Vector3 Pos = Vector3((float)(X * (64)), (float)(Y * (64)), -5);
	Vector3 PreScale = Vector3((float)X, (float)Y, (float)-5);
	Vector3 UpScale = (PreScale - selectedCell_1);

	Vector2 RenderScale;


	SetPosition(Pos);

	//activeCellSprite->SetSpriteSize(XMUINT2(tileScale * mapScale, tileScale * mapScale));
	if (cellSelected)
	{
		UpScale = (PreScale - selectedCell_1);

	}
	


	if (Inputs::InputManager::IsMouseButtonPressed(Inputs::InputManager::LButton) && wasMouseReleased)
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
	else if (!wasMouseReleased && !Inputs::InputManager::IsMouseButtonPressed(Inputs::InputManager::LButton))
	{
		wasMouseReleased = true;
	}

	if (Inputs::InputManager::IsMouseButtonPressed(Inputs::InputManager::RButton))
	{
		CWorldManager::GetEditorWorld()->ShouldInspectEntity(Vector2(PreScale.x, PreScale.y));
		if (cellSelected)
		{
			CWorldManager::GetEditorWorld()->ClearQueue();
			
		

			cellSelected = false;
		}
	}

	if (Inputs::InputManager::IsKeyReleased(Inputs::InputManager::C))
	{
		CWorldManager::GetEditorWorld()->SetOperationMode(EditOperationMode::None);
	}
	if (Inputs::InputManager::IsKeyReleased(Inputs::InputManager::W))
	{
		CWorldManager::GetEditorWorld()->SetOperationMode(EditOperationMode::Move_Entity);
	}
	if (Inputs::InputManager::IsKeyReleased(Inputs::InputManager::Delete))
	{
		CWorldManager::GetEditorWorld()->RemoveSelectedEntity();
	}
	
	//mouseCalc. * -1;


	


	//activeCellSprite->SetSpriteSize(XMUINT2(X1, Y2));
	
	
	

	
}


