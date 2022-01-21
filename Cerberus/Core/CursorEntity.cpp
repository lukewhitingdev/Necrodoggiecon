#include "CursorEntity.h"
#include "Utility/DebugOutput/Debug.h"
#include "../CTextRenderComponent.h"
#include <sstream>
#include "CCamera.h"

CursorEntity::CursorEntity()
{
	sprite = AddComponent<CSpriteComponent>();
	sprite->LoadTexture("Resources\\cursorSS.dds");
	sprite->SetRenderRect(XMUINT2(16, 16));
	sprite->SetSpriteSize(XMUINT2(64, 64));
	sprite->SetPosition(0, 0, -100);

	text = AddComponent<CTextRenderComponent>();
	text->justification = TextJustification::Center;
}

void CursorEntity::Update(float deltaTime)
{
	timeElapsed += deltaTime;

	const float speed = 2;
	sprite->SetTextureOffset(XMFLOAT2(round(timeElapsed * speed) * 16, 0));

	float invZoom = 1 / Engine::camera.GetZoom();
	SetPosition(Vector3(((Input::mousePos.x - Engine::windowWidth * 0.5f) * invZoom) + Engine::camera.GetCameraPosition().x,
		((-Input::mousePos.y + Engine::windowHeight * 0.5f) * invZoom) + Engine::camera.GetCameraPosition().y,
		-100));

	text->SetScale(invZoom);
	sprite->SetScale(invZoom);
	text->SetPosition(0, -48 * invZoom, -100);

	/*if (Input::GetKeyState(Keys::LMB))
		sprite->SetRotation(3.14159 / 4);
	else
		sprite->SetRotation(0);*/

	std::stringstream ss;
	ss << "X:" << round(GetPosition().x) << " Y:" << round(GetPosition().y);
	text->SetText(ss.str());
}

CursorEntity::~CursorEntity()
{

}
