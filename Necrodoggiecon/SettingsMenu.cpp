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
#include "Cerberus\Core\Utility\Audio\AudioController.h"

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
	masterVolumeText = this->CreateVolumeUI(Vector2(0, 150), MasterVolumeTitle, masterVolume ,std::bind(&SettingsMenu::MasterVolumeUp, this), std::bind(&SettingsMenu::MasterVolumeDown, this));

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

void SettingsMenu::Update(float deltaTime)
{
	if(masterVolumeText != nullptr)
	{
		masterVolumeText->GetText()->SetText(std::to_string(masterVolume));
	}
	CWidget_Canvas::Update(deltaTime);
}

CWidget_Text* SettingsMenu::CreateVolumeUI(Vector2 pos, const std::string& title, const int& volume, std::function<void()> volumeUp, std::function<void()> volumeDown)
{
	std::string null = "";
	int offset = pos.y;
	CWidget_Text* VolumeTitle = CreateText(Vector2(0, offset), Vector2(.5, .5), -165, null);
	VolumeTitle->GetText()->SetFont("Resources/Engine/font.png");
	VolumeTitle->GetText()->SetText(title);
	VolumeTitle->GetText()->SetScale(1, 1, 1);

	CWidget_Text* Volume = CreateText(Vector2(0, offset - 30), Vector2(.5, .5), -165, null);
	Volume->GetText()->SetFont("Resources/Engine/font.png");
	Volume->GetText()->SetText(std::to_string(volume));
	Volume->GetText()->SetScale(1, 1, 1);

	CWidget_Button* VolumeUp = CreateButton(Vector2(40, offset - 30), Vector2(.5, .5), null, -165);
	VolumeUp->Bind_OnButtonReleased(volumeUp);
	VolumeUp->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	VolumeUp->GetSprite()->SetTint(DirectX::XMFLOAT4(0.0f, 140.0f, 0.0f, 1.0f));
	VolumeUp->SetButtonSize(Vector2(25, 25));

	CWidget_Button* VolumeDown = CreateButton(Vector2(-40, offset - 30), Vector2(.5, .5), null, -165);
	VolumeDown->Bind_OnButtonReleased(volumeDown);
	VolumeDown->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	VolumeDown->GetSprite()->SetTint(DirectX::XMFLOAT4(140.0f, 0.0f, 0.0f, 1.0f));
	VolumeDown->SetButtonSize(Vector2(25, 25));

	return Volume;
};

void SettingsMenu::MasterVolumeUp()
{
	SoundManager::PlaySound("UIClick", Vector3(0, 0, 0));
	AudioController::SetMaxVolumeForEmitterType((masterVolume >= 100) ? 100 : masterVolume++, EMITTERTYPE::ALL);
}

void SettingsMenu::MasterVolumeDown()
{
	SoundManager::PlaySound("UIClick", Vector3(0, 0, 0));
	AudioController::SetMaxVolumeForEmitterType((masterVolume <= 0) ? 0 : masterVolume--, EMITTERTYPE::ALL);
}
