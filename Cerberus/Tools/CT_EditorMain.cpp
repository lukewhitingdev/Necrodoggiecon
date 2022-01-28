#include "CT_EditorMain.h"
#include "CT_EditorWindows.h"
#include "CT_EditorGrid.h"



CT_EditorMain::CT_EditorMain()
{
	editorWindow = new CT_EditorWindows();
	CT_EditorGrid* grid = Engine::CreateEntity<CT_EditorGrid>();
	grid->SetupGrid();
}

void CT_EditorMain::Initialise()
{




}

void CT_EditorMain::RenderWindows()
{
	editorWindow->render();
}
