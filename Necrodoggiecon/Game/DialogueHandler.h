#pragma once
#include <Cerberus/Core/CEntity.h>
#include <Game/DialogueUI.h>

class DialogueHandler : public CEntity
{
private:
	static DialogueUI* dialogueUI;
public:
	DialogueHandler();
	~DialogueHandler();
	static void SetDialogue(std::string name, std::string dialogue, bool instantDisplay);
};

