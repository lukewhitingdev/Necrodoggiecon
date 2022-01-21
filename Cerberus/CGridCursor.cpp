#include "CGridCursor.h"
#include "CSpriteComponent.h"
#include "CWorld.h"
#include "Engine.h"
#include "CCamera.h"

CGridCursor::CGridCursor()
{
	Offset = Vector3(0, 0, 0);

	ActiveCellSprite = AddComponent<CSpriteComponent>();
	ActiveCellSprite->LoadTexture("Resources\\Tiles\\ActiveCell.dds");

	ActiveCellSprite->SetRenderRect(XMUINT2(tileScale, tileScale));
	ActiveCellSprite->SetSpriteSize(XMUINT2(tileScale, tileScale));
	ActiveCellSprite->SetTextureOffset(XMFLOAT2(0, 0));
}

void CGridCursor::Update(float deltaTime)
{

	if (!Inputs::InputManager::IsMouseButtonPressed(Inputs::InputManager::RButton))
	{
		if (screenMoved)
		{
			Offset = Offset + (Offset_Start - Offset_End);
			screenMoved = false;
		}
		
		

		Vector3 mousePos = Inputs::InputManager::mousePos;
		Vector3 MousePos2 = Vector3(Inputs::InputManager::mousePos.x - Engine::windowWidth * 0.5f, -Inputs::InputManager::mousePos.y + Engine::windowHeight * 0.5f, -100);

		MousePos2 /= Engine::camera.GetZoom();

		//Vector3 mouseCalc = Vector3(-mousePos.x + Engine::camera.GetCameraPosition().x, (mousePos.y) + Engine::camera.GetCameraPosition().y, -15);

		Vector3 camPos = Vector3(Engine::camera.GetCameraPosition().x, Engine::camera.GetCameraPosition().y, -10);

		//Vector3 OffsetCalc = ((Offset - Offset_Start));

		Vector3 mouseCalc = MousePos2 + Offset;
		//mouseCalc. * -1;
		SetPosition(mouseCalc);
		


	}
	else
	{
		if (!screenMoved)
		{
			screenMoved = true;
			Offset_Start = GetPosition();
		}
		Offset_End - GetPosition();
	}
	

	
}
