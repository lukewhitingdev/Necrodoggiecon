/*****************************************************************//**
 * \file   LevelSelectMenu.cpp
 * \brief  The cpp for the level select menu
 * 
 * \author Jack B
 * \date   May 2022
 *********************************************************************/
#include "LevelSelectMenu.h"
#include "Cerberus/Core/UI/CWidget_Button.h"
#include "Cerberus/Core/UI/CWidget_Image.h"
#include "Cerberus/Core/Components/CTextRenderComponent.h"
#include "Cerberus/Core/Utility/CUIManager.h"
#include "Cerberus/Core/UI/CWidget_Text.h"
#include "Cerberus/Core/Utility/CWorldManager.h"
#include "CWorld_Game.h"
#include "Necrodoggiecon/TransitionHelper.h"
#include "Game/SoundManager.h"

LevelSelectMenu::LevelSelectMenu()
{
	InitialiseCanvas();
}

/**
 * creates all the buttons for later use.
 * 
 */
void LevelSelectMenu::InitialiseCanvas()
{
	CWidget_Image* Background = CreateImage(Vector2(0, 0), Vector2(.5, .5), -140);
	Background->GetSprite()->LoadTextureWIC("Resources/Game/uiBackground.png");
	Background->GetSprite()->SetRenderRect(XMUINT2(16, 16));
	Background->GetSprite()->SetSpriteSize(XMUINT2(5000, 5000));
	Background->GetSprite()->SetUseTranslucency(true);
	Background->GetSprite()->SetTint(XMFLOAT4(-255, -255, -255, 0));

	std::string TitleText = "Level Select";
	CWidget_Text* Title = CreateText(Vector2(0, 240), Vector2(.5, .5), -165, TitleText);
	Title->GetText()->SetFont("Resources/Engine/font.png");
	Title->GetText()->SetText(TitleText);
	Title->GetText()->SetScale(2, 2, 1);

	std::string CloseButtonName = "Back";
	CWidget_Button* CloseButton = CreateButton(Vector2(0, -258), Vector2(.5, .5), CloseButtonName, -165);
	CloseButton->Bind_OnButtonReleased(std::bind(&LevelSelectMenu::CloseMenu, this));
	CloseButton->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	CloseButton->SetButtonSize(Vector2(256, 110));

	std::string PlayButtonName = "Play";
	CWidget_Button* PlayButton = CreateButton(Vector2(0, -128), Vector2(.5, .5), PlayButtonName, -165);
	PlayButton->Bind_OnButtonReleased(std::bind(&LevelSelectMenu::PlayLevel, this));
	PlayButton->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	PlayButton->SetButtonSize(Vector2(256, 110));

	std::string LVL0name = "Tutorial";
	LVL0 = CreateButton(Vector2(0, 50), Vector2(.5, .5), LVL0name, -165);
	LVL0->Bind_OnButtonReleased(std::bind(&LevelSelectMenu::OpenLevelTutorial, this));
	LVL0->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	LVL0->SetButtonSize(Vector2(256, 256));

	std::string LVL1name = "Level 1";
	LVL1 = CreateButton(Vector2(300, 50), Vector2(.5, .5), LVL1name, -165);
	LVL1->Bind_OnButtonReleased(std::bind(&LevelSelectMenu::OpenLevel1, this));
	LVL1->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	LVL1->SetButtonSize(Vector2(256, 256));
	
	std::string LVL2name = "Level 2";
	LVL2 = CreateButton(Vector2(600, 50), Vector2(.5, .5), LVL2name, -165);
	LVL2->Bind_OnButtonReleased(std::bind(&LevelSelectMenu::OpenLevel2, this));
	LVL2->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	LVL2->SetButtonSize(Vector2(256, 256));
	
	std::string LVL3name = "Level 3";
	LVL3 = CreateButton(Vector2(900, 50), Vector2(.5, .5), LVL3name, -165);
	LVL3->Bind_OnButtonReleased(std::bind(&LevelSelectMenu::OpenLevel3, this));
	LVL3->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	LVL3->SetButtonSize(Vector2(256, 256));
	
	std::string LVL4name = "Level 4";
	LVL4 = CreateButton(Vector2(1200, 50), Vector2(.5, .5), LVL4name, -165);
	LVL4->Bind_OnButtonReleased(std::bind(&LevelSelectMenu::OpenLevel4, this));
	LVL4->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	LVL4->SetButtonSize(Vector2(256, 256));
	
	std::string LVL5name = "Level 5";
	LVL5 = CreateButton(Vector2(1500, 50), Vector2(.5, .5), LVL5name, -165);
	LVL5->Bind_OnButtonReleased(std::bind(&LevelSelectMenu::OpenLevel5, this));
	LVL5->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	LVL5->SetButtonSize(Vector2(256, 256));
	
	std::string LVL6name = "Level 6";
	LVL6 = CreateButton(Vector2(1800, 50), Vector2(.5, .5), LVL6name, -165);
	LVL6->Bind_OnButtonReleased(std::bind(&LevelSelectMenu::OpenLevel6, this));
	LVL6->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	LVL6->SetButtonSize(Vector2(256, 256));
	
	std::string LVL7name = "Level 7";
	LVL7 = CreateButton(Vector2(2100, 50), Vector2(.5, .5), LVL7name, -165);
	LVL7->Bind_OnButtonReleased(std::bind(&LevelSelectMenu::OpenLevel7, this));
	LVL7->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	LVL7->SetButtonSize(Vector2(256, 256));

	SetVisibility(false);
}

/**
 * closes menu and reveals main menu.
 * 
 */
void LevelSelectMenu::CloseMenu()
{
	SoundManager::PlaySound("UIClick", Vector3(0, 0, 0));
	SetVisibility(false);
	CUIManager::GetCanvas("MainMenu")->SetVisibility(true);
	Debug::Log("closing settings");
}

/**
 * moves selected level to center.
 * 
 */
void LevelSelectMenu::OpenLevelTutorial()
{
	SoundManager::PlaySound("UIClick", Vector3(0, 0, 0));
	SelectedLevel = 0;
	UpdateButtonPositions();
}
/**
 * moves selected level to center.
 *
 */
void LevelSelectMenu::OpenLevel1()
{
	SoundManager::PlaySound("UIClick", Vector3(0, 0, 0));
	SelectedLevel = 1;
	UpdateButtonPositions();
}
/**
 * moves selected level to center.
 *
 */
void LevelSelectMenu::OpenLevel2()
{
	SoundManager::PlaySound("UIClick", Vector3(0, 0, 0));
	SelectedLevel = 2;
	UpdateButtonPositions();
}
/**
 * moves selected level to center.
 *
 */
void LevelSelectMenu::OpenLevel3()
{
	SoundManager::PlaySound("UIClick", Vector3(0, 0, 0));
	SelectedLevel = 3;
	UpdateButtonPositions();

}
/**
 * moves selected level to center.
 *
 */
void LevelSelectMenu::OpenLevel4()
{
	SoundManager::PlaySound("UIClick", Vector3(0, 0, 0));
	SelectedLevel = 4;
	UpdateButtonPositions();

}
/**
 * moves selected level to center.
 *
 */
void LevelSelectMenu::OpenLevel5()
{
	SoundManager::PlaySound("UIClick", Vector3(0, 0, 0));
	SelectedLevel = 5;
	UpdateButtonPositions();

}
/**
 * moves selected level to center.
 *
 */
void LevelSelectMenu::OpenLevel6()
{
	SoundManager::PlaySound("UIClick", Vector3(0, 0, 0));
	SelectedLevel = 6;
	UpdateButtonPositions();

}
/**
 * moves selected level to center.
 *
 */
void LevelSelectMenu::OpenLevel7()
{
	SoundManager::PlaySound("UIClick", Vector3(0, 0, 0));
	SelectedLevel = 7;
	UpdateButtonPositions();

}
/**
 * offsets all level buttons to show which is selected.
 *
 */
void LevelSelectMenu::UpdateButtonPositions()
{
	LVL0->SetWidgetTransform(Vector2((0*300)-(300*SelectedLevel), 50), Vector2(.5, .5),-165);
	LVL1->SetWidgetTransform(Vector2((1*300)-(300*SelectedLevel), 50), Vector2(.5, .5),-165);
	LVL2->SetWidgetTransform(Vector2((2*300)-(300*SelectedLevel), 50), Vector2(.5, .5),-165);
	LVL3->SetWidgetTransform(Vector2((3*300)-(300*SelectedLevel), 50), Vector2(.5, .5),-165);
	LVL4->SetWidgetTransform(Vector2((4*300)-(300*SelectedLevel), 50), Vector2(.5, .5),-165);
	LVL5->SetWidgetTransform(Vector2((5*300)-(300*SelectedLevel), 50), Vector2(.5, .5),-165);
	LVL6->SetWidgetTransform(Vector2((6*300)-(300*SelectedLevel), 50), Vector2(.5, .5),-165);
	LVL7->SetWidgetTransform(Vector2((7*300)-(300*SelectedLevel), 50), Vector2(.5, .5),-165);
}
/**
 * Loads the currently selected level.
 * 
 */
void LevelSelectMenu::PlayLevel()
{
	SetVisibility(false);
	TransitionHelper::OpenLevel(SelectedLevel, false);


}
