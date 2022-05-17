#include "DialogueHandler.h"
#include "Cerberus/Core/Engine.h"
#include <Game/DialogueUI.h>

DialogueUI* DialogueHandler::dialogueUI = nullptr;

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

	dialogueUI->SetName(name);
	dialogueUI->SetText(dialogue, instantDisplay);
}
