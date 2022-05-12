#pragma once
#include "CEntity.h"
class CT_EditorMain 
{
public:
	CT_EditorMain();

	void Initialise();

	~CT_EditorMain();

	void RenderWindows();

	class CT_EditorGrid* grid;
	
	class CT_EditorWindows* editorWindow;

};




