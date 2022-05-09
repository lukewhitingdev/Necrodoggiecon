#pragma once
class CWorldManager
{
	static void LoadWorld(int Slot, bool bEditorMode);

	static void UnloadWorld();

	static class CWorld* GetWorld() {
		return ActiveWorld;
	}





private: 

	static CWorld* GameWorld;
	static CWorld_Editable* EditorWorld;
};

