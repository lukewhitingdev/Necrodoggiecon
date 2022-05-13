#include "Necrodoggiecon/Game/TestUI.h"
#include "Cerberus\Core\Components\CAnimationSpriteComponent.h"
#include "Cerberus\Core\Components\CTextRenderComponent.h"
#include "Cerberus\Core\Components\CSpriteComponent.h"
#include "Cerberus\Core\Structs\CCamera.h"
#include "Cerberus\Core\Utility\CameraManager\CameraManager.h"
#include <sstream>

TestUI::TestUI()
{
	SetPosition(0, 0, -100);

	birb = AddComponent<CAnimationSpriteComponent>();
	birb->LoadTextureWIC("Resources\\birb.png");
	birb->SetRenderRect(XMUINT2(128, 128));
	birb->SetSpriteSize(XMUINT2(128, 128));
	birb->SetPosition(560, -296, 0);
	birb->SetAnchor(XMFLOAT2(1, 1));
	birb->SetAnimationRectSize(XMUINT2(5, 2));

	text1 = AddComponent<CTextRenderComponent>();
	text1->SetJustification(TextJustification::Right);
	text1->SetPosition(-625, -146, 0);
	text1->SetAnchor(XMFLOAT2(0, 1));

	text2 = AddComponent<CTextRenderComponent>();
	text2->SetJustification(TextJustification::Right);
	text2->SetPosition(-625, -126, 0);
	text2->SetAnchor(XMFLOAT2(0, 1));

	text3 = AddComponent<CTextRenderComponent>();
	text3->SetJustification(TextJustification::Center);
	text3->SetReserveCount(24);
	text3->SetPosition(560, -255, 0);
	text3->SetText("");
	text3->SetAnchor(XMFLOAT2(1, 1));

	textFPS = AddComponent<CTextRenderComponent>();
	textFPS->SetJustification(TextJustification::Left);
	textFPS->SetReserveCount(12);
	textFPS->SetPosition(640, 346, 0);
	textFPS->SetText("");
	textFPS->SetAnchor(XMFLOAT2(1, 0));
	
	for (CComponent* e : components)
		e->ui = true;
}

void TestUI::Update(float deltaTime)
{
	CCameraComponent* camera = CameraManager::GetRenderingCamera();

	if (camera == nullptr)
		return;

	timeElapsed += deltaTime;
	textTimer += deltaTime; 
	fpsTimer += deltaTime;
	framesTotal++;

	if (textTimer >= 5)
	{
		textTimer = 0;

		size_t index = rand() % (texts.size() * 2);

		if(index < texts.size())
			text3->SetText(texts[index]);
		else
			text3->SetText("");
	}

	std::stringstream ss;
	ss << "Zoom:" << camera->GetZoomLevel();
	text1->SetText(ss.str());

	ss.str("");
	ss << "X:" << round(camera->GetPosition().x) << " Y:" << round(camera->GetPosition().y);
	text2->SetText(ss.str());

	if (fpsTimer > 0.5)
	{
		unsigned int time = (unsigned int)round(1 / (fpsTimer / float(framesTotal)));
		fpsTimer = 0;
		framesTotal = 0;

		ss.str("");
		ss << time << " FPS";
		textFPS->SetText(ss.str());
	}
}

TestUI::~TestUI()
{

}
