#include "CT_EditorMain.h"
#include "CT_EditorWindows.h"
#include "CT_EditorGrid.h"



CT_EditorMain::CT_EditorMain()
{
	editorWindow = new CT_EditorWindows();
	grid = Engine::CreateEntity<CT_EditorGrid>();
	grid->SetupGrid();
}

void CT_EditorMain::Initialise()
{




}

CT_EditorMain::~CT_EditorMain()
{
	Engine::DestroyEntity(grid);
	delete(editorWindow);
}

void CT_EditorMain::RenderWindows()
{
	editorWindow->render();
}
