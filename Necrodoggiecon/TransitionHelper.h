#pragma once
class TransitionHelper
{
	static int queueSlot;
	static bool queueMenu;
public:
	static void OpenLevel(int Slot, bool isMenu);

	static void OpenQueuedLevel();
};

