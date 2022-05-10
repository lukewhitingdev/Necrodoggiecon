#pragma once
#include "Core/Environment/CWorld_Edit.h"



class CWorldManager
{
public:
	static void LoadWorld(int Slot, bool bEditorMode);
	static void LoadWorld(CWorld* World);
	static void LoadWorld(CWorld_Editable* World);


	static class CWorld* GetWorld() {
		return GameWorld;
	}

	static class CWorld_Editable* GetEditorWorld() {
		return EditorWorld;
	}



private: 

	static CWorld* GameWorld;
	static CWorld_Editable* EditorWorld;
};

