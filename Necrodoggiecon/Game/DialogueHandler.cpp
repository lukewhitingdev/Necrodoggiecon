#include "DialogueHandler.h"
#include "Cerberus/Core/Engine.h"
#include <Game/DialogueUI.h>
#include <fstream>
#include "Cerberus\Dependencies\NlohmannJson\json.hpp"

DialogueUI* DialogueHandler::dialogueUI = nullptr;
std::vector<Dialogue*> DialogueHandler::currentDialogue;
int DialogueHandler::curDialogueIndex = 0;

DialogueHandler::DialogueHandler()
{
}

DialogueHandler::~DialogueHandler()
{
}

void DialogueHandler::SetDialogue(std::string name, std::string dialogue, bool instantDisplay)
{
	if (dialogueUI == nullptr)
		dialogueUI = Engine::CreateEntity<DialogueUI>();

	dialogueUI->ToggleDrawing(true);
	dialogueUI->SetName(name);
	dialogueUI->SetText(dialogue, instantDisplay);
}

void DialogueHandler::LoadDialogue(std::string jsonPath, std::string dialogueName)
{
	std::ifstream file(jsonPath);
	nlohmann::json storedFile;
	file >> storedFile;

	if (storedFile[dialogueName].is_null() || storedFile[dialogueName]["ListOfDialogue"].is_null()) return;

	currentDialogue.clear();

	for (auto &array : storedFile[dialogueName]["ListOfDialogue"])
	{
		if (array["Name"].is_null() || array["Dialogue"].is_null()) return;

		currentDialogue.push_back(new Dialogue(array["Name"], array["Dialogue"]));
	}

	if (!currentDialogue.empty())
		SetDialogue(currentDialogue[0]->name, currentDialogue[0]->dialogue, false);

	curDialogueIndex = 0;
}
void DialogueHandler::AdvanceDialogue()
{
	if (dialogueUI == nullptr)
		dialogueUI = Engine::CreateEntity<DialogueUI>();

	dialogueUI->ToggleDrawing(true);

	if (dialogueUI->IsUpdating())
		dialogueUI->CompletePage();
	else if (dialogueUI->GetReserveCharacterCount() > 0)
		dialogueUI->Advance();
	else if (!currentDialogue.empty())
	{
		curDialogueIndex++;
		if (curDialogueIndex < currentDialogue.size())
		{
			dialogueUI->Advance();
			SetDialogue(currentDialogue[curDialogueIndex]->name, currentDialogue[curDialogueIndex]->dialogue, false);
		}
		else
			CloseDialogue();
	}
	else
		CloseDialogue();

}
void DialogueHandler::CloseDialogue()
{
	if (dialogueUI == nullptr) return;
	
	dialogueUI->ClearText();
	dialogueUI->ToggleDrawing(false);
}