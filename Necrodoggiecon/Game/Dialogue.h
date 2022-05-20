#pragma once

struct Dialogue
{
public:
	std::string name;
	std::string dialogue;

	Dialogue(std::string name, std::string dialogue) : dialogue(dialogue), name(name)
	{

	}
};

