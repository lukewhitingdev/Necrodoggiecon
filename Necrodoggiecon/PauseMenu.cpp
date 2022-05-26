/*****************************************************************//**
 * \file   PauseMenu.cpp
 * \brief  The cpp for the pause menu 
 * 
 * \author Jack B
 * \date   May 2022
 *********************************************************************/
#include "PauseMenu.h"
#include "Cerberus/Core/UI/CWidget_Button.h"
#include "Cerberus/Core/UI/CWidget_Image.h"
#include "Cerberus/Core/Components/CTextRenderComponent.h"
#include "Cerberus/Core/Utility/CWorldManager.h"
#include "CWorld_Game.h"
#include "Cerberus/Core/UI/CWidget_Text.h"
#include "Cerberus/Core/Utility/CUIManager.h"
#include "SettingsMenu.h"
#include "LevelCompleteMenu.h"
#include "Game/SoundManager.h"
#include "Necrodoggiecon/CWorld_Menu.h"

PauseMenu::PauseMenu()
{
	InitialiseCanvas();
}
/**
 * Initialise buttons and the settings menu.
 * 
 */
void PauseMenu::InitialiseCanvas()
{
	Debug::Log("Pause Canvas Initialised");

	CWidget_Image* Background = CreateImage(Vector2(0, 0), Vector2(.5, .5), -150);
	Background->GetSprite()->LoadTextureWIC("Resources/Game/uiBackground.png");
	Background->GetSprite()->SetRenderRect(XMUINT2(16, 16));
	Background->GetSprite()->SetSpriteSize(XMUINT2(1500, 1000));
	Background->GetSprite()->SetUseTranslucency(true);
	Background->GetSprite()->SetTint(XMFLOAT4(-255, -255, -255, -0.1f));

	std::string TitleText = "Paused";
	CWidget_Text* Title = CreateText(Vector2(0, 280), Vector2(1, 1), -165, TitleText);
	Title->GetText()->SetFont("Resources/Engine/font.png");
	Title->GetText()->SetText(TitleText);
	Title->GetText()->SetScale(2, 2, 1);

	std::string ResumeButtonName = "Resume";
	CWidget_Button* Resume = CreateButton(Vector2(0, 188), Vector2(1, 1), ResumeButtonName, -155);
	Resume->Bind_OnButtonReleased(std::bind(&PauseMenu::ResumeGame , this));
	Resume->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	Resume->SetButtonSize(Vector2(256, 110));

	std::string SettingsButtonName = "Settings";
	CWidget_Button* Settings = CreateButton(Vector2(0, 68), Vector2(1, 1), SettingsButtonName, -155);
	Settings->Bind_OnButtonReleased(std::bind(&PauseMenu::OpenSettingsMenu, this));
	Settings->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	Settings->SetButtonSize(Vector2(256, 110));

	std::string QuitButtonName = "Quit to Menu";
	CWidget_Button* Exit = CreateButton(Vector2(0, -60), Vector2(1, 1), QuitButtonName, -155);
	Exit->Bind_OnButtonReleased(std::bind(&PauseMenu::QuitToMenu , this));
	Exit->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	Exit->SetButtonSize(Vector2(256, 110));
	Exit->GetText()->SetScale(1, 1, 1);
	
	std::string FullQuitButtonName = "Quit to Desktop";
	CWidget_Button* ExitFull = CreateButton(Vector2(0, -188), Vector2(1, 1), FullQuitButtonName, -155);
	ExitFull->Bind_OnButtonReleased(std::bind(&PauseMenu::QuitToDesktop , this));
	ExitFull->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	ExitFull->SetButtonSize(Vector2(256, 110));

	CUIManager::AddCanvas(Engine::CreateEntity<SettingsMenu>(), "SettingsMenu");
	CUIManager::AddCanvas(Engine::CreateEntity<LevelCompleteMenu>(), "LevelCompleteMenu");

	SetVisibility(false);
}
/**
 * pauses game.
 * 
 */
void PauseMenu::PauseGame()
{
	SoundManager::PlaySound("UIClick", Vector3(0, 0, 0));
	SetVisibility(true);
	Debug::Log("pause");
	isPaused = true;
}
/**
 * resumes game.
 * 
 */
void PauseMenu::ResumeGame()
{
	SoundManager::PlaySound("UIClick", Vector3(0, 0, 0));
	SetVisibility(false);
	Debug::Log("resume");
	isPaused = false;
}
/**
 * returns to main menu.
 * 
 */
void PauseMenu::QuitToMenu()
{
	SoundManager::PlaySound("UIClick", Vector3(0, 0, 0));
	Debug::Log("quit to menu");
	CWorldManager::LoadWorld(new CWorld_Menu());
}
/**
 * closes game.
 * 
 */
void PauseMenu::QuitToDesktop()
{
	SoundManager::PlaySound("UIClick", Vector3(0, 0, 0));
	Debug::Log("quit to desktop");
	PostQuitMessage(1);
}
/**
 * listens for input to open/close pause menu through button.
 * 
 * \param deltaTime
 */
void PauseMenu::Update(float deltaTime)
{
	CWidget_Canvas::Update(deltaTime);
	if (InputManager::IsKeyPressed(InputManager::Escape) && !gameEnded)
	{
		pausePressedDown = true;
	}
	if (InputManager::IsKeyReleased(InputManager::Escape) && !gameEnded && pausePressedDown)
	{
		if (isPaused)
		{
			ResumeGame();
		}
		else
		{
			PauseGame();
		}
		pausePressedDown = false;
	}


	if (InputManager::IsKeyPressed(InputManager::Tab))
	{
		CUIManager::GetCanvas("LevelCompleteMenu")->SetVisibility(true);
		gameEnded = true;
	}

}
/**
 * opens settings.
 * 
 */
void PauseMenu::OpenSettingsMenu()
{
	SoundManager::PlaySound("UIClick", Vector3(0, 0, 0));
	Debug::Log("open settings");
	CUIManager::GetCanvas("SettingsMenu")->SetVisibility(true);
	SetVisibility(false);
}