#include "CGridCursor.h"
#include "CSpriteComponent.h"
#include "CWorld.h"
#include "Engine.h"
#include "CCamera.h"

CGridCursor::CGridCursor()
{


	ActiveCellSprite = AddComponent<CSpriteComponent>();
	ActiveCellSprite->LoadTexture("Resources\\Tiles\\ActiveCell.dds");

	ActiveCellSprite->SetRenderRect(XMUINT2(tileScale, tileScale));
	ActiveCellSprite->SetSpriteSize(XMUINT2(tileScale, tileScale));
	ActiveCellSprite->SetTextureOffset(XMFLOAT2(0, 0));
}

void CGridCursor::Update(float deltaTime)
{

	Vector3 mousePos = Inputs::InputManager::mousePos;
	mousePos /= Engine::camera.GetZoom();
	
	//Vector3 mouseCalc = Vector3(-mousePos.x + Engine::camera.GetCameraPosition().x, (mousePos.y) + Engine::camera.GetCameraPosition().y, -15);

	Vector3 camPos = Vector3(Engine::camera.GetCameraPosition().x, Engine::camera.GetCameraPosition().y, -10);
	
	

	Vector3 mouseCalc = camPos + (mousePos - camPos);
	//mouseCalc. * -1;
	SetPosition(mouseCalc);
}
