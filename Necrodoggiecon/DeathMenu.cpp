#include "DeathMenu.h"
#include "LevelCompleteMenu.h"
#include "Cerberus/Core/UI/CWidget_Button.h"
#include "Cerberus/Core/UI/CWidget_Image.h"
#include "Cerberus/Core/Components/CTextRenderComponent.h"
#include "Cerberus/Core/Utility/CWorldManager.h"
#include "CWorld_Game.h"
#include "Cerberus/Core/UI/CWidget_Text.h"
#include "Cerberus/Core/Utility/CUIManager.h"
#include "Game/SoundManager.h"
#include "Necrodoggiecon/CWorld_Menu.h"

void DeathMenu::InitialiseCanvas()
{
	Debug::Log("Pause Canvas Initialised");

	CWidget_Image* Background = CreateImage(Vector2(0, 0), Vector2(.5, .5), -150);
	Background->GetSprite()->LoadTextureWIC("Resources/Game/uiBackground.png");
	Background->GetSprite()->SetRenderRect(XMUINT2(16, 16));
	Background->GetSprite()->SetSpriteSize(XMUINT2(5000, 5000));
	Background->GetSprite()->SetUseTranslucency(true);
	Background->GetSprite()->SetTint(XMFLOAT4(-255, -255, -255, -0.1f));

	std::string TitleText = "You died!";
	CWidget_Text* Title = CreateText(Vector2(0, 280), Vector2(.5, .5), -165, TitleText);
	Title->GetText()->SetFont("Resources/Engine/font.png");
	Title->GetText()->SetText(TitleText);
	Title->GetText()->SetScale(2, 2, 1);

	std::string QuitButtonName = "Quit to Menu";
	CWidget_Button* Exit = CreateButton(Vector2(0, -60), Vector2(.5, .5), QuitButtonName, -155);
	Exit->Bind_OnButtonReleased(std::bind(&DeathMenu::QuitToMenu, this));
	Exit->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	Exit->SetButtonSize(Vector2(256, 110));
	Exit->GetText()->SetScale(1, 1, 1);

	std::string FullQuitButtonName = "Quit to Desktop";
	CWidget_Button* ExitFull = CreateButton(Vector2(0, -188), Vector2(.5, .5), FullQuitButtonName, -155);
	ExitFull->Bind_OnButtonReleased(std::bind(&DeathMenu::QuitToDesktop, this));
	ExitFull->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	ExitFull->SetButtonSize(Vector2(256, 110));

	std::string NxtLvlName = "Retry Level";
	CWidget_Button* NxtLvl = CreateButton(Vector2(0, 68), Vector2(.5, .5), NxtLvlName, -155);
	NxtLvl->Bind_OnButtonPressed(std::bind(&DeathMenu::restartLevel, this));
	NxtLvl->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	NxtLvl->SetButtonSize(Vector2(256, 110));

	SetVisibility(false);
}

DeathMenu::DeathMenu()
{
	InitialiseCanvas();
}

void DeathMenu::QuitToMenu()
{
	SoundManager::PlaySound("UIClick", Vector3(0, 0, 0));
	Debug::Log("quit to menu");
	Engine::paused = false;
	CWorldManager::LoadWorld(new CWorld_Menu());
}

void DeathMenu::QuitToDesktop()
{
	SoundManager::PlaySound("UIClick", Vector3(0, 0, 0));
	Debug::Log("quit to desktop");
	PostQuitMessage(1);
}

void DeathMenu::restartLevel()
{
	SoundManager::PlaySound("UIClick", Vector3(0, 0, 0));
	Debug::Log("restart level");
	Engine::paused = false;
	CWorldManager::LoadWorld(new CWorld_Game(CWorldManager::GetWorld()->GetMapSlot()));
}
