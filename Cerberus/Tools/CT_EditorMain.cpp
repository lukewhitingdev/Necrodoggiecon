#include "CT_EditorMain.h"
#include "CT_EditorWindows.h"
#include "CT_EditorGrid.h"



CT_EditorMain::CT_EditorMain()
{
	EditorWindow = new CT_EditorWindows();
	CT_EditorGrid* Grid = Engine::CreateEntity<CT_EditorGrid>();
	Grid->SetupGrid();
}

void CT_EditorMain::Initialise()
{




}

void CT_EditorMain::RenderWindows()
{
	EditorWindow->render();
}
