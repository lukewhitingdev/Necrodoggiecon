#include "EventSystem.h"

std::map<std::string, std::vector<std::function<void()>>> EventSystem::events;

void EventSystem::AddListener(std::string eventID, std::function<void()> functionToAdd)
{
	// Check if the event doesnt exist.
	if (events.find(eventID) == events.end())
	{
		// Create an empty event list.
		events.emplace(std::pair<std::string, std::vector<std::function<void()>>>(eventID, std::vector<std::function<void()>>()));
	}

	events.at(eventID).push_back(functionToAdd);		// Add the callback function to our list of listeners for the event.
}

void EventSystem::TriggerEvent(std::string eventID)
{
	// Check if the event exists.
	if (events.find(eventID) != events.end())
	{
		std::vector<std::function<void()>> eventList = events.at(eventID);

		// Loop through all subscribed events and trigger them.
		for (std::function<void()> function : eventList)
		{
			function();
		}
	}else
	{
		Debug::LogError("[EventSystem] Tried to trigger an event that doesnt exist! EventID: %s", eventID);
	}
}
