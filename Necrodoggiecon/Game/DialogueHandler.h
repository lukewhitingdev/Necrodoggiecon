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
	static bool instantDisplay;
public:
	DialogueHandler();
	~DialogueHandler();
	static void SetDialogue(std::string name, std::string dialogue);
	static void LoadDialogue(std::string jsonPath, std::string dialogueName);
	static void AdvanceDialogue();
	static void CloseDialogue();
	static void SetInstantDisplay(bool _instantDisplay) { instantDisplay = _instantDisplay; }
};

