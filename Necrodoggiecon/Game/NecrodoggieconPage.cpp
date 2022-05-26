#include "NecrodoggieconPage.h"
#include "Game/SoundManager.h"
#include "Game/DialogueHandler.h"
#include "Cerberus/Core/Utility/EventSystem/EventSystem.h"


void NecrodoggieconPage::OnInteract()
{
	EventSystem::AddListener("DialogueClose", std::bind(&NecrodoggieconPage::OnDialogueClose, this));
	SoundManager::PlaySound("LevelClear", GetPosition());
	DialogueHandler::LoadDialogue("Resources/Game/Dialogue.json", std::to_string(GetSlot()) + "End");
}

void NecrodoggieconPage::OnDialogueClose()
{
	LevelTransporter::OnInteract();
}
