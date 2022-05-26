/*****************************************************************//**
 * \file   MainMenu.cpp
 * \brief  The cpp for the main menu
 * 
 * \author Jack B
 * \date   May 2022
 *********************************************************************/
#include "MainMenu.h"
#include "Cerberus/Core/UI/CWidget_Button.h"
#include "Cerberus/Core/UI/CWidget_Image.h"
#include "Cerberus/Core/UI/CWidget_Text.h"
#include "Cerberus/Core/Utility/CWorldManager.h"
#include "CWorld_Game.h"
#include "Cerberus/Core/Utility/CUIManager.h"
#include "SettingsMenu.h"
#include "LevelSelectMenu.h"

MainMenu::MainMenu()
{
	SetIsUI(true);
	InitialiseCanvas();
}
/**
 * ititialises buttons and the settings + level select canvases.
 * 
 */
void MainMenu::InitialiseCanvas()
{
	Debug::Log("Canvas Initialised");
	
	CWidget_Image* Background = CreateImage(Vector2(0, 0), Vector2(.5, .5), -140);
	Background->GetSprite()->LoadTextureWIC("Resources/Game/uiBackground.png");
	Background->GetSprite()->SetRenderRect(XMUINT2(16, 16));
	Background->GetSprite()->SetSpriteSize(XMUINT2(5000, 5000));
	Background->GetSprite()->SetUseTranslucency(true);
	Background->GetSprite()->SetTint(XMFLOAT4(-255, -255, -255, 0));

	std::string TitleText = "Necrodogicon";
	CWidget_Text* Title = CreateText(Vector2(0, 188), Vector2(.5, .5),-155, TitleText);
	Title->GetText()->SetFont("Resources/Engine/font.png");
	Title->GetText()->SetText(TitleText);
	Title->GetText()->SetScale(2,2,1);

	std::string FullQuitButtonName = "Quit";
	CWidget_Button* ExitFull = CreateButton(Vector2(0, -188), Vector2(.5, .5), FullQuitButtonName, -145);
	ExitFull->Bind_OnButtonReleased(std::bind(&MainMenu::QuitToDesktop, this));
	ExitFull->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	ExitFull->SetButtonSize(Vector2(256, 110));
	
	std::string Level1Name = "Level Select";
	CWidget_Button* Lvl1 = CreateButton(Vector2(0, 68), Vector2(.5, .5), Level1Name, -145);
	Lvl1->Bind_OnButtonReleased(std::bind(&MainMenu::OpenLevelSelect, this));
	Lvl1->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	Lvl1->SetButtonSize(Vector2(256, 110));

	std::string Lvl2Name = "Settings";
	CWidget_Button* Lvl2 = CreateButton(Vector2(0, -60), Vector2(.5, .5), Lvl2Name, -145);
	Lvl2->Bind_OnButtonReleased(std::bind(&MainMenu::OpenSettingsMenu, this));
	Lvl2->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	Lvl2->SetButtonSize(Vector2(256, 110));

	CUIManager::AddCanvas(Engine::CreateEntity<SettingsMenu>(), "SettingsMenu");
	CUIManager::AddCanvas(Engine::CreateEntity<LevelSelectMenu>(), "LevelSelectMenu");
}

/**
 * closes game.
 * 
 */
void MainMenu::QuitToDesktop()
{
	Debug::Log("quit to desktop");
	PostQuitMessage(1);
}
/**
 * opens level select menu.
 * 
 */
void MainMenu::OpenLevelSelect()
{
	Debug::Log("open level select");
	CUIManager::GetCanvas("LevelSelectMenu")->SetVisibility(true);
	SetVisibility(false);
}
/**
 * opens settings menu.
 * 
 */
void MainMenu::OpenSettingsMenu()
{
	Debug::Log("open settings");
	CUIManager::GetCanvas("SettingsMenu")->SetVisibility(true);
	SetVisibility(false);
}
