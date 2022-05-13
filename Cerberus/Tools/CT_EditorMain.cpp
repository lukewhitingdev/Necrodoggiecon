#include "CT_EditorMain.h"
#include "CT_EditorWindows.h"
#include "CT_EditorGrid.h"
#include "Core/Components/CCameraComponent.h"
#include "Cerberus/Core/Utility/CameraManager/CameraManager.h"


CT_EditorMain::CT_EditorMain()
{
	editorWindow = new CT_EditorWindows();
	grid = Engine::CreateEntity<CT_EditorGrid>();
	CCameraComponent* cam = grid->AddComponent<CCameraComponent>();

	CameraManager::AddCamera(cam);

	CameraManager::SetRenderingCamera(cam);
	cam->SetAttachedToParent(false);
	cam->SetPosition(Vector3(tileScale * (mapScale / 2)));
	cam->SetParent(nullptr);
	cam->SetPosition(cam->GetPosition().x, cam->GetPosition().y, 0);
	grid->SetupGrid(cam);

	

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
