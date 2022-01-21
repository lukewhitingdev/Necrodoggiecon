#include "CT_EditorMain.h"
#include "CT_WindowBase.h"
#include "CT_Window_ToolBar.h"



CT_EditorMain::CT_EditorMain()
{
	EditorWindow = new CT_WindowBase();
}

void CT_EditorMain::Initialise()
{




}

void CT_EditorMain::RenderWindows()
{
	EditorWindow->render();
}
