#include "MainMenu.h"
#include "Cerberus/Core/UI/CWidget_Button.h"


MainMenu::MainMenu()
{
	InitialiseCanvas();
}

void MainMenu::InitialiseCanvas()
{
	Debug::Log("Canvas Initialised");

	for (int i = 0; i < 5; i++)
	{
		CWidget_Button* Test = CreateButton(Vector2(0, 32 * i), Vector2(1, 1), "Test Button", 0);
		Test->Bind_OnButtonPressed(std::bind(&MainMenu::TestButtonPressed, this));
		Test->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
		Test->SetSize(Vector2(64, 32));
	}

}

void MainMenu::TestButtonPressed()
{
	Debug::Log("Test Button has been pressed");
}
