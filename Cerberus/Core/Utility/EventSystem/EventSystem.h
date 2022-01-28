#pragma once
#include <map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include "Utility/DebugOutput/Debug.h"
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

