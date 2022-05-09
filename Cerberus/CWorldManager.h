#pragma once
class CWorldManager
{
	static void LoadWorld(int Slot);

	static class CWorld* GetWorld() {
		return ActiveWorld;
	}





private: 

	static CWorld* ActiveWorld;
};

