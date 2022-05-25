/*****************************************************************//**
 * \file   EventSystem.h
 * \brief  A generic event system to allow for code to exectute across the engine without direct references.
 *
 * \author Luke Whiting
 * \date   Jan 2022
 *********************************************************************/

#pragma once
#include <map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include "Cerberus/Core/Utility/DebugOutput/Debug.h"
class EventSystem
{
public:
	// Adds a function to the event list of the specified eventID.
	static void AddListener(std::string eventID, std::function<void()> functionToAdd);

	// Triggers all functions that are listening on the specified eventID.
	static void TriggerEvent(std::string eventID);
	
private:
	static std::map<std::string, std::vector<std::function<void()>>> events;
};

