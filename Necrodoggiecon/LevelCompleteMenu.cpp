/*****************************************************************//**
 * \file   LevelCompleteMenu.cpp
 * \brief  cpp for setting up the level complete screen
 * 
 * \author Jack B
 * \date   May 2022
 *********************************************************************/
#include "LevelCompleteMenu.h"
#include "Cerberus/Core/UI/CWidget_Button.h"
#include "Cerberus/Core/UI/CWidget_Image.h"
#include "Cerberus/Core/Components/CTextRenderComponent.h"
#include "Cerberus/Core/Utility/CWorldManager.h"
#include "CWorld_Game.h"
#include "Cerberus/Core/UI/CWidget_Text.h"
#include "Cerberus/Core/Utility/CUIManager.h"
#include "Necrodoggiecon/CWorld_Menu.h"

LevelCompleteMenu::LevelCompleteMenu()
{
	InitialiseCanvas();
}
/**
 * initialises buttons and only shows next level button if there is a next level.
 * 
 */
void LevelCompleteMenu::InitialiseCanvas()
{
	Debug::Log("Pause Canvas Initialised");

	CWidget_Image* Background = CreateImage(Vector2(0, 0), Vector2(.5, .5), -150);
	Background->GetSprite()->LoadTextureWIC("Resources/Game/uiBackground.png");
	Background->GetSprite()->SetRenderRect(XMUINT2(16, 16));
	Background->GetSprite()->SetSpriteSize(XMUINT2(1500, 1000));
	Background->GetSprite()->SetUseTranslucency(true);
	Background->GetSprite()->SetTint(XMFLOAT4(-255, -255, -255, -0.1f));

	std::string TitleText = "Level complete!";
	CWidget_Text* Title = CreateText(Vector2(0, 280), Vector2(1, 1), -165, TitleText);
	Title->GetText()->SetFont("Resources/Engine/font.png");
	Title->GetText()->SetText(TitleText);
	Title->GetText()->SetScale(2, 2, 1);

	std::string QuitButtonName = "Quit to Menu";
	CWidget_Button* Exit = CreateButton(Vector2(0, -60), Vector2(1, 1), QuitButtonName, -155);
	Exit->Bind_OnButtonReleased(std::bind(&LevelCompleteMenu::QuitToMenu, this));
	Exit->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	Exit->SetButtonSize(Vector2(256, 110));
	Exit->GetText()->SetScale(1, 1, 1);

	std::string FullQuitButtonName = "Quit to Desktop";
	CWidget_Button* ExitFull = CreateButton(Vector2(0, -188), Vector2(1, 1), FullQuitButtonName, -155);
	ExitFull->Bind_OnButtonReleased(std::bind(&LevelCompleteMenu::QuitToDesktop, this));
	ExitFull->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	ExitFull->SetButtonSize(Vector2(256, 110));

	//if (CWorldManager::GetWorld() < 7)
	//{
		std::string NxtLvlName = "Next Level";
		CWidget_Button* NxtLvl = CreateButton(Vector2(0, 68), Vector2(1, 1), NxtLvlName, -155);
		NxtLvl->Bind_OnButtonPressed(std::bind(&LevelCompleteMenu::NextLevel, this));
		NxtLvl->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
		NxtLvl->SetButtonSize(Vector2(256, 110));
	//}

	SetVisibility(false);
}
/**
 * quits back to main menu.
 * 
 */
void LevelCompleteMenu::QuitToMenu()
{
	Debug::Log("quit to menu");
	CWorldManager::LoadWorld(new CWorld_Menu());
}
/**
 * quits game entirely.
 * 
 */
void LevelCompleteMenu::QuitToDesktop()
{
	Debug::Log("quit to desktop");
	PostQuitMessage(1);
}
/**
 * loads next level.
 * 
 */
void LevelCompleteMenu::NextLevel()
{
	Debug::Log("load next level");
	CWorldManager::LoadWorld(new CWorld_Game(CWorldManager::GetWorld()->GetMapSlot()+1));
}