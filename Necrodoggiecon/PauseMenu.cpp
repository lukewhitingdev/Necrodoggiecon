#include "PauseMenu.h"
#include "Cerberus/Core/UI/CWidget_Button.h"
#include "Cerberus/Core/UI/CWidget_Image.h"

PauseMenu::PauseMenu()
{
	InitialiseCanvas();
}

void PauseMenu::InitialiseCanvas()
{
	Debug::Log("Pause Canvas Initialised");
	std::string ResumeButtonName = "ResumeButton";
	CWidget_Button* Resume = CreateButton(Vector2(0, 32), Vector2(1, 1), ResumeButtonName, 5);
	Resume->Bind_OnButtonPressed(std::bind(&PauseMenu::ResumeGame , this));
	Resume->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	Resume->SetButtonSize(Vector2(64, 32));
	Resume->SetScale(2, 2, 1);

	SetVisibility(false);
}

void PauseMenu::PauseGame()
{
	SetVisibility(true);
}

void PauseMenu::ResumeGame()
{
	SetVisibility(false);
	Debug::Log("resume");
}

void PauseMenu::QuitToMenu()
{

}