#pragma once
#include "Cerberus/Core/Environment/CWorld_Edit.h"



class CWorldManager
{
public:
	static void LoadWorld(int Slot, bool bEditorMode);
	static void LoadWorld(CWorld* World);
	static void LoadWorld(CWorld_Editable* World);


	static class CWorld* GetWorld() {
		return gameWorld;
	}

	static class CWorld_Editable* GetEditorWorld() {
		return editorWorld;
	}



private: 

	static CWorld* gameWorld;
	static CWorld_Editable* editorWorld;
};

