#pragma once
#include "Cerberus\Core\CEntity.h"
class CT_EditorMain 
{
public:
	CT_EditorMain();

	void Initialise();


	void RenderWindows();
	
	class CT_EditorWindows* editorWindow;

};




