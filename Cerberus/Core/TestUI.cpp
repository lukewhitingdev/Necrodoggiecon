#include "TestUI.h"
#include "CTextRenderComponent.h"
#include "CSpriteComponent.h"

TestUI::TestUI()
{
	SetPosition(0, 0, -100);

	birb = AddComponent<CSpriteComponent>();
	birb->LoadTexture("Resources\\birb.dds");
	birb->SetRenderRect(XMUINT2(128, 128));
	birb->SetSpriteSize(XMUINT2(128, 128));
	birb->SetPosition(560, -280, 0);

	text1 = AddComponent<CTextRenderComponent>();
	text1->justification = TextJustification::Right;
	text1->SetText("This is some UI");
	text1->SetPosition(-560, -280, 0);

	for (CComponent* e : components)
		e->ui = true;
}

void TestUI::Update(float deltaTime)
{
	timeElapsed += deltaTime;

	const uint32_t speed = 24;
	birb->SetTextureOffset(XMFLOAT2(round(timeElapsed * speed) * 128, float((int(round(timeElapsed * speed) / 5) % 2)) * 128));
}

TestUI::~TestUI()
{

}
