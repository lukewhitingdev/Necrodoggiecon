#include "CT_EditorMain.h"
#include "CT_EditorWindows.h"
#include "CT_EditorGrid.h"
#include "Core/Components/CCameraComponent.h"



CT_EditorMain::CT_EditorMain()
{
	editorWindow = new CT_EditorWindows();
	CT_EditorGrid* grid = Engine::CreateEntity<CT_EditorGrid>();
	CCameraComponent* cam = grid->AddComponent<CCameraComponent>();
	grid->SetupGrid(cam);
}

void CT_EditorMain::Initialise()
{




}

void CT_EditorMain::RenderWindows()
{
	editorWindow->render();
}
