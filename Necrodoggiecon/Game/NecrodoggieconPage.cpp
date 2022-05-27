#include "NecrodoggieconPage.h"
#include "NecrodoggieconPage.h"
#include "Game/SoundManager.h"
#include "Game/DialogueHandler.h"
#include "Cerberus/Core/Utility/EventSystem/EventSystem.h"
#include "Cerberus/Core/Utility/CWorldManager.h"
#include "CWorld_Menu.h"


NecrodoggieconPage::NecrodoggieconPage()
{
	SetTextureWIC("Resources/Game/The Necrodoggiecon/The Necrodoggiecon page 1.png");
}

NecrodoggieconPage::~NecrodoggieconPage()
{
}

void NecrodoggieconPage::OnInteract()
{
	SoundManager::PlaySound("LevelClear", GetPosition());
	CWorldManager::LoadWorld(new CWorld_Menu());
	//EventSystem::AddListener("DialogueClose", std::bind(&NecrodoggieconPage::OnDialogueClose, this));
	//DialogueHandler::LoadDialogue("Resources/Game/Dialogue.json", std::to_string(GetSlot()) + "End");
}

void NecrodoggieconPage::OnDialogueClose()
{
	CWorldManager::LoadWorld(new CWorld_Menu());
}
