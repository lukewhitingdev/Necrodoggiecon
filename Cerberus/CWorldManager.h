#pragma once
#include "Core/Environment/CWorld_Edit.h"



class CWorldManager
{
public:
	static void LoadWorld(int Slot, bool bEditorMode);


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

