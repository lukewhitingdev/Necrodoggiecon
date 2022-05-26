#include "MainMenu.h"
#include "Cerberus/Core/UI/CWidget_Button.h"
#include "Cerberus/Core/UI/CWidget_Image.h"

#include "Cerberus/Core/Components/CSpriteComponent.h"


MainMenu::MainMenu()
{
	SetIsUI(true);
	InitialiseCanvas();
}

void MainMenu::InitialiseCanvas()
{
	Debug::Log("Canvas Initialised");
	
	//CWidget_Image* Background = CreateImage(Vector2(0,65), Vector2(0,0), -5);
	//Background->GetSprite()->LoadTexture("Resources/UI/UI_ButtonAtlas.dds");
	//Background->GetSprite()->SetSpriteSize(DirectX::XMUINT2(75, 175));
	//Background->GetSprite()->SetRenderRect(DirectX::XMUINT2(64, 32));
	
	std::string ButtonName = "Test Buttons";
	std::string SampleText = "Main Menu";

	CreateText(Vector2(0,250), Vector2(0,0), 2, SampleText);

	for (int i = 0; i < 5; i++)
	{
		CWidget_Button* Test = CreateButton(Vector2(0, 32 * i), Vector2(1, 1), ButtonName, 5);
		Test->Bind_OnButtonPressed(std::bind(&MainMenu::TestButtonPressed, this));
		Test->SetTexture("Resources/UI/UI_ButtonAtlas.dds");
		Test->SetButtonSize(Vector2(64, 32));
	}

}

void MainMenu::TestButtonPressed()
{
	Debug::Log("Test Button has been pressed");
}
