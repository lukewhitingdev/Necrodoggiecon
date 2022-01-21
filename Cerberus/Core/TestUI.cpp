#include "TestUI.h"
#include "CTextRenderComponent.h"
#include "CSpriteComponent.h"
#include "CCamera.h"
#include <sstream>

TestUI::TestUI()
{
	SetPosition(0, 0, -100);

	birb = AddComponent<CSpriteComponent>();
	birb->LoadTexture("Resources\\birb.dds");
	birb->SetRenderRect(XMUINT2(128, 128));
	birb->SetSpriteSize(XMUINT2(128, 128));
	birb->SetPosition(560, -280, 0);
	birb->SetAnchor(XMFLOAT2(1, 0));

	text1 = AddComponent<CTextRenderComponent>();
	text1->justification = TextJustification::Right;
	text1->SetPosition(-580, -320, 0);
	text1->SetAnchor(XMFLOAT2(0, 0));

	text2 = AddComponent<CTextRenderComponent>();
	text2->justification = TextJustification::Right;
	text2->SetPosition(-580, -300, 0);
	text2->SetAnchor(XMFLOAT2(0, 0));

	text3 = AddComponent<CTextRenderComponent>();
	text3->justification = TextJustification::Right;
	text3->SetReserveCount(32);
	text3->SetPosition(-580, 300, 0);
	text3->SetText(texts[rand() % 7]);
	text3->SetAnchor(XMFLOAT2(0, 1));
	
	for (CComponent* e : components)
		e->ui = true;
}

void TestUI::Update(float deltaTime)
{
	timeElapsed += deltaTime;
	timeElapsed2 += deltaTime;

	const uint32_t speed = 24;
	birb->SetTextureOffset(XMFLOAT2(round(timeElapsed * speed) * 128, float((int(round(timeElapsed * speed) / 5) % 2)) * 128));

	if (int(floor(timeElapsed2 * .2)) % 2)
	{
		timeElapsed2 = 0;
		text3->SetText(texts[rand() % 7]);
	}

	std::stringstream ss;
	ss << "Zoom:" << Engine::camera.GetZoom();
	text1->SetText(ss.str());

	ss.str("");
	ss << "X:" << round(Engine::camera.GetCameraPosition().x) << " Y:" << round(Engine::camera.GetCameraPosition().y);
	text2->SetText(ss.str());
}

TestUI::~TestUI()
{

}
