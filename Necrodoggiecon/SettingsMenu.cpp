/*****************************************************************//**
 * \file   SettingsMenu.cpp
 * \brief  The cpp for the settings menu
 * 
 * \author Jack B
 * \date   May 2022
 *********************************************************************/
#include "SettingsMenu.h"
#include "Cerberus/Core/UI/CWidget_Button.h"
#include "Cerberus/Core/UI/CWidget_Image.h"
#include "Cerberus/Core/Components/CTextRenderComponent.h"
#include "Cerberus/Core/Utility/CUIManager.h"
#include "Cerberus/Core/UI/CWidget_Text.h"
#include "Game/SoundManager.h"

SettingsMenu::SettingsMenu()
{
	InitialiseCanvas();
}

/**
 * creates buttons and other.
 * 
 */
void SettingsMenu::InitialiseCanvas()
{
	CWidget_Image* Background = CreateImage(Vector2(0, 0), Vector2(.5, .5), -160);
	Background->GetSprite()->LoadTextureWIC("Resources/Game/uiBackground.png");
	Background->GetSprite()->SetRenderRect(XMUINT2(16, 16));
	Background->GetSprite()->SetSpriteSize(XMUINT2(5000, 5000));
	Background->GetSprite()->SetUseTranslucency(true);
	Background->GetSprite()->SetTint(XMFLOAT4(-255, -255, -255, -0.1f));

	std::string TitleText = "Settings";
	CWidget_Text* Title = CreateText(Vector2(0, 188), Vector2(.5, .5), -165, TitleText);
	Title->GetText()->SetFont("Resources/Engine/font.png");
	Title->GetText()->SetText(TitleText);
	Title->GetText()->SetScale(2, 2, 1);

	std::string CloseButtonName = "Close";
	CWidget_Button* CloseButton = CreateButton(Vector2(0, -188), Vector2(.5, .5), CloseButtonName, -165);
	CloseButton->Bind_OnButtonReleased(std::bind(&SettingsMenu::CloseSettings, this));
	CloseButton->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	CloseButton->SetButtonSize(Vector2(256, 110));

	SetVisibility(false);
}

/**
 * closes settings and re-opens either main menu or pause menu depending on which is applicable.
 * 
 */
void SettingsMenu::CloseSettings()
{
	SoundManager::PlaySound("UIClick", Vector3(0, 0, 0));
	if (CUIManager::GetCanvas("MainMenu") != nullptr)
	{
		SetVisibility(false);
		CUIManager::GetCanvas("MainMenu")->SetVisibility(true);
		Debug::Log("closing settings");
	}
	if (CUIManager::GetCanvas("PauseMenu") != nullptr)
	{
		SetVisibility(false);
		CUIManager::GetCanvas("PauseMenu")->SetVisibility(true);
		Debug::Log("closing settings");
	}
}