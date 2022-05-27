#include "EventSystem.h"

std::map<std::string, std::vector<std::function<void()>>> EventSystem::events;

/**
 * Adds a listener to a specific event ID.
 * 
 * \param eventID eventID that will trigger this event
 * \param functionToAdd function that will be triggered when the event is called.
 */
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

/**
 * Removes a listener for a specific event ID.
 * 
 * \param eventID the eventID you wish to remove.
 */
void EventSystem::RemoveListener(std::string eventID)
{
	// Check if the event doesnt exist.
	if (events.find(eventID) != events.end())
	{
		// Create an empty event list.
		events.erase(eventID);
	}
	else
	{
		Debug::LogError("Tried to remove a listener that doesnt exist from eventID: %s", eventID.c_str());
		return;
	}
}

/**
 * Triggers the event of specified ID.
 * 
 * \param eventID eventID of the specific event that is triggered.
 */
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
		Debug::LogError("[EventSystem] Tried to trigger an event that doesnt exist! EventID: %s", eventID.c_str());
	}
}
