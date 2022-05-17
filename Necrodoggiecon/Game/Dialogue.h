#pragma once

struct Dialogue
{
public:
	std::string name;
	std::string dialogue;

	Dialogue(std::string _name, std::string _dialogue) : dialogue(_dialogue), name(_name)
	{

	}
};

