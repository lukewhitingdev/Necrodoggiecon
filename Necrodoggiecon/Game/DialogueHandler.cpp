#include "DialogueHandler.h"
#include "Cerberus/Core/Engine.h"
#include <Game/DialogueUI.h>
#include <fstream>
#include "Cerberus\Dependencies\NlohmannJson\json.hpp"
#include <Cerberus/Core/Utility/EventSystem/EventSystem.h>
/*****************************************************************//**
 * \file   DialogueHandler.cpp
 * \brief  Static class used to control dialogue, including the loading of dialogue from a json.
 *
 * \author Cathan Bertram
 * \date   May 2022
 *********************************************************************/

DialogueUI* DialogueHandler::dialogueUI = nullptr;
std::vector<Dialogue*> DialogueHandler::currentDialogue;
int DialogueHandler::curDialogueIndex = 0;
bool DialogueHandler::instantDisplay = false;
DialogueHandler::DialogueHandler()
{
}

DialogueHandler::~DialogueHandler()
{
}
/**
* Function to set the dialogue that should display. Calls the SetName and SetText functions on the dialogueUI
*/
void DialogueHandler::SetDialogue(const std::string& name, const std::string& dialogue)
{
	if (dialogueUI == nullptr)
		dialogueUI = Engine::CreateEntity<DialogueUI>();

	dialogueUI->ToggleDrawing(true);
	dialogueUI->SetName(name);
	dialogueUI->SetText(dialogue, instantDisplay);
}
/**
* Function to load dialogue from a json file. Will the call the SetDialogue function using the first instance of dialogue in the json file.
* Called Like DialogueHandler::LoadDialogue("Resources/Game/Dialogue.json", "TestDialogue")
*/
void DialogueHandler::LoadDialogue(const std::string& jsonPath, const std::string& dialogueName)
{
	std::ifstream file(jsonPath);
	if (!file.is_open())
	{
		std::string errorMessage = "Couldn't open file at path: " + jsonPath;
		Debug::LogError(errorMessage.c_str());
		return;
	}
	nlohmann::json storedFile;
	file >> storedFile;

	if (storedFile[dialogueName].is_null())
	{
		std::string errorMessage = "Path: " + dialogueName + " does not exist in the json file";
		Debug::LogError(errorMessage.c_str());
		return;
	}
	if (storedFile[dialogueName]["ListOfDialogue"].is_null())
	{
		std::string errorMessage = "Path: ListOfDialogue does not exist in the json file after path: " + dialogueName;
		Debug::LogError(errorMessage.c_str());
		return;
	}

	currentDialogue.clear();

	for (auto &array : storedFile[dialogueName]["ListOfDialogue"])
	{
		if (array["Name"].is_null())
		{
			std::string errorMessage = "Path: Name does not exist in the json file after path: " + dialogueName + ", ListOfDialogue";
			Debug::LogError(errorMessage.c_str());
			return;
		}
		if (array["Dialogue"].is_null())
		{
			std::string errorMessage = "Path: Dialogue does not exist in the json file after path: " + dialogueName + ", ListOfDialogue";
			Debug::LogError(errorMessage.c_str());
			return;
		}

		currentDialogue.push_back(new Dialogue(array["Name"], array["Dialogue"]));
	}

	if (!currentDialogue.empty())
		SetDialogue(currentDialogue[0]->name, currentDialogue[0]->dialogue);

	curDialogueIndex = 0;

	if(dialogueUI != nullptr)
		EventSystem::TriggerEvent("DialogueOpen");

}
/**
* Function used to move dialogue to the next stage. Will either complete the current page, go to the next page, load the next piece of dialogue or close the dialogue UI
*/
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
			SetDialogue(currentDialogue[curDialogueIndex]->name, currentDialogue[curDialogueIndex]->dialogue);
		}
		else
			CloseDialogue();
	}
	else
		CloseDialogue();

}
/**
* Function to clear the text on the dialogue UI and disable drawing.
*/
void DialogueHandler::CloseDialogue()
{
	if (dialogueUI == nullptr) return;
	
	dialogueUI->ClearText();
	dialogueUI->ToggleDrawing(false);
	EventSystem::TriggerEvent("DialogueClose");
}