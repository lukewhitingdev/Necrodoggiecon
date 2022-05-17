#pragma once
#include <Cerberus/Core/CEntity.h>
#include <Game/DialogueUI.h>
#include <Game/Dialogue.h>

class DialogueHandler : public CEntity
{
private:
	static DialogueUI* dialogueUI;
	static std::vector<Dialogue*> currentDialogue;
	static int curDialogueIndex;
public:
	DialogueHandler();
	~DialogueHandler();
	static void SetDialogue(std::string name, std::string dialogue, bool instantDisplay);
	static void LoadDialogue(std::string jsonPath, std::string dialogueName);
	static void AdvanceDialogue();
	static void CloseDialogue();
};

