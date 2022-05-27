#pragma once
#include "Cerberus\Core\CEntity.h"
class CT_EditorMain 
{
public:
	CT_EditorMain();

	~CT_EditorMain();

	void RenderWindows();

	class CT_EditorGrid* grid;
	
	class CT_EditorWindows* editorWindow;

};




