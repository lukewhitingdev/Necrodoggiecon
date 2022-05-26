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
	
	std::string MasterVolumeTitle = "Master Volume";
	this->CreateVolumeUI(Vector2(0, 150), MasterVolumeTitle, std::bind(&SettingsMenu::MasterVolumeUp, this), std::bind(&SettingsMenu::MasterVolumeDown, this));

	std::string AmbientVolumeTitle = "Ambient Volume";
	this->CreateVolumeUI(Vector2(0, 90), AmbientVolumeTitle, std::bind(&SettingsMenu::AmbientVolumeUp, this), std::bind(&SettingsMenu::AmbientVolumeDown, this));

	std::string SFXVolumeTitle = "SFX Volume";
	this->CreateVolumeUI(Vector2(0, 30), SFXVolumeTitle, std::bind(&SettingsMenu::SFXVolumeUp, this), std::bind(&SettingsMenu::SFXVolumeDown, this));

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

void SettingsMenu::CreateVolumeUI(Vector2 pos, std::string& title, std::function<void()> volumeUp, std::function<void()> volumeDown)
{
	std::string null = "";
	int offset = pos.y;
	CWidget_Text* MasterVolumeTitle = CreateText(Vector2(0, offset), Vector2(.5, .5), -165, null);
	MasterVolumeTitle->GetText()->SetFont("Resources/Engine/font.png");
	MasterVolumeTitle->GetText()->SetText(title);
	MasterVolumeTitle->GetText()->SetScale(1, 1, 1);

	CWidget_Text* MasterVolume = CreateText(Vector2(0, offset - 30), Vector2(.5, .5), -165, null);
	MasterVolume->GetText()->SetFont("Resources/Engine/font.png");
	MasterVolume->GetText()->SetText("100");
	MasterVolume->GetText()->SetScale(1, 1, 1);

	CWidget_Button* MasterVolumeUp = CreateButton(Vector2(40, offset - 30), Vector2(.5, .5), null, -165);
	MasterVolumeUp->Bind_OnButtonReleased(volumeUp);
	MasterVolumeUp->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	MasterVolumeUp->GetSprite()->SetTint(DirectX::XMFLOAT4(0.0f, 140.0f, 0.0f, 1.0f));
	MasterVolumeUp->SetButtonSize(Vector2(25, 25));

	CWidget_Button* MasterVolumeDown = CreateButton(Vector2(-40, offset - 30), Vector2(.5, .5), null, -165);
	MasterVolumeDown->Bind_OnButtonReleased(volumeDown);
	MasterVolumeDown->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	MasterVolumeDown->GetSprite()->SetTint(DirectX::XMFLOAT4(140.0f, 0.0f, 0.0f, 1.0f));
	MasterVolumeDown->SetButtonSize(Vector2(25, 25));
};

void SettingsMenu::MasterVolumeUp()
{
	Debug::Log("Master Volume Up");
}

void SettingsMenu::MasterVolumeDown()
{
	Debug::Log("Master Volume Down");
}

void SettingsMenu::AmbientVolumeUp()
{
	Debug::Log("Ambient Volume Up");
}

void SettingsMenu::AmbientVolumeDown()
{
	Debug::Log("Ambient Volume Down");
}

void SettingsMenu::SFXVolumeUp()
{
	Debug::Log("SFX Volume Up");
}

void SettingsMenu::SFXVolumeDown()
{
	Debug::Log("SFX Volume Down");
}
