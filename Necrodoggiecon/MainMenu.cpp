#include "MainMenu.h"
#include "Cerberus/Core/UI/CWidget_Button.h"
#include "Cerberus/Core/UI/CWidget_Image.h"
#include "Cerberus/Core/UI/CWidget_Text.h"
#include "Cerberus/Core/Utility/CWorldManager.h"
#include "CWorld_Game.h"

MainMenu::MainMenu()
{
	InitialiseCanvas();
}

void MainMenu::InitialiseCanvas()
{
	Debug::Log("Canvas Initialised");
	
	CWidget_Image* Background = CreateImage(Vector2(0, 0), Vector2(.5, .5), -150);
	Background->GetSprite()->LoadTextureWIC("Resources/Game/uiBackground.png");
	Background->GetSprite()->SetRenderRect(XMUINT2(16, 16));
	Background->GetSprite()->SetSpriteSize(XMUINT2(1500, 1000));
	Background->GetSprite()->SetUseTranslucency(true);
	Background->GetSprite()->SetTint(XMFLOAT4(-255, -255, -255, 0));

	std::string TitleText = "Necrodogicon";
	CWidget_Text* Title = CreateText(Vector2(0, 188), Vector2(1, 1),-155, TitleText);
	Title->GetText()->SetFont("Resources/Engine/font.png");
	Title->GetText()->SetText(TitleText);
	Title->GetText()->SetScale(2,2,1);

	std::string FullQuitButtonName = "Quit";
	CWidget_Button* ExitFull = CreateButton(Vector2(0, -188), Vector2(1, 1), FullQuitButtonName, -155);
	ExitFull->Bind_OnButtonPressed(std::bind(&MainMenu::QuitToDesktop, this));
	ExitFull->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	ExitFull->SetButtonSize(Vector2(256, 110));
	
	std::string Level1Name = "Level 1";
	CWidget_Button* Lvl1 = CreateButton(Vector2(0, 68), Vector2(1, 1), Level1Name, -155);
	Lvl1->Bind_OnButtonPressed(std::bind(&MainMenu::LoadLevel1, this));
	Lvl1->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	Lvl1->SetButtonSize(Vector2(256, 110));

	std::string Lvl2Name = "Level 2";
	CWidget_Button* Lvl2 = CreateButton(Vector2(0, -60), Vector2(1, 1), Lvl2Name, -155);
	Lvl2->Bind_OnButtonPressed(std::bind(&MainMenu::LoadLevel2, this));
	Lvl2->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	Lvl2->SetButtonSize(Vector2(256, 110));


}

void MainMenu::QuitToDesktop()
{
	Debug::Log("quit to desktop");
	PostQuitMessage(1);
}

void MainMenu::LoadLevel1()
{
	Debug::Log("load level 1");
	CWorldManager::LoadWorld(new CWorld_Game(0));
}
void MainMenu::LoadLevel2()
{
	Debug::Log("load level 2");
	CWorldManager::LoadWorld(new CWorld_Game(1));
}
