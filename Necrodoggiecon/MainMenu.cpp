#include "MainMenu.h"
#include "Cerberus/Core/UI/CWidget_Button.h"


MainMenu::MainMenu()
{
	InitialiseCanvas();
}

void MainMenu::InitialiseCanvas()
{
	CWidget_Button* Test = CreateButton(500, 500, "Test Button", 0);
	Test->Bind_OnButtonPressed(std::bind(&MainMenu::TestButtonPressed,this));
	Test->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
	Test->SetSize(Vector2(64, 32));

}

void MainMenu::TestButtonPressed()
{
	Debug::Log("Test Button has been pressed");
}
