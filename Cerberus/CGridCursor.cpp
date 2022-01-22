#include "CGridCursor.h"
#include "CSpriteComponent.h"
#include "CWorld.h"
#include "Engine.h"
#include "CCamera.h"
#include <DirectXMath.h>

CGridCursor::CGridCursor()
{
	Offset = Vector3(0, 0, 0);

	ActiveCellSprite = AddComponent<CSpriteComponent>();
	ActiveCellSprite->LoadTexture("Resources\\Tiles\\ActiveCell.dds");

	ActiveCellSprite->SetRenderRect(XMUINT2(tileScale, tileScale));
	ActiveCellSprite->SetSpriteSize(XMUINT2(tileScale, tileScale));
	ActiveCellSprite->SetTextureOffset(XMFLOAT2(0, 0));
	
	SetScale(2, 2, 2);

	screenMoved = false;
}

void CGridCursor::Update(float deltaTime)
{


	Vector3 camPos = Vector3(Engine::camera.GetCameraPosition().x, Engine::camera.GetCameraPosition().y, -10);

	Vector3 MousePos2 = Vector3(Inputs::InputManager::mousePos.x - Engine::windowWidth * 0.5f, -Inputs::InputManager::mousePos.y + Engine::windowHeight * 0.5f, -100);


	MousePos2 /= Engine::camera.GetZoom();


	//mouseCalc. * -1;
	SetPosition(MousePos2 + camPos);

	




	
	
	
	

	
}

Vector2 CGridCursor::ScreenToWorld(Vector2 Pos)
{

	


	

	float width = Engine::windowWidth;
	float height = Engine::windowHeight;

	float u = Pos.x / width;
	float v = (height - Pos.y) / height;

	float ratio = width / height;
	Vector2 extent = Vector2(25.0f, 25.0f);
	extent *= Engine::camera.GetZoom();

	Vector2 lower = Vector2(Engine::camera.GetCameraPosition().x, Engine::camera.GetCameraPosition().y) - extent;
	Vector2 upper = Vector2(Engine::camera.GetCameraPosition().x, Engine::camera.GetCameraPosition().y) + extent;

	Vector2 pw = Vector2(((1.0f - u) * lower.x + u * upper.x), ((1.0 - v) * lower.y, +v * upper.y));
	
	
	return pw;
	
}
