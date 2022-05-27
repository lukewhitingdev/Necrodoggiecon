/*****************************************************************//**
 * \file   CT_EditorMain.cpp
 * \brief  Container class for the Editor interface.
 * 
 * \author Samuel Elliot Jackson
 * \date   May 2022
 *********************************************************************/
#include "CT_EditorMain.h"
#include "CT_EditorWindows.h"
#include "CT_EditorGrid.h"
#include "Core/Components/CCameraComponent.h"
#include "Cerberus/Core/Utility/CameraManager/CameraManager.h"

/**
 * Default constructor for EditorMain, Instantiates Grid, Wditor Windows and triggers grid setup.
 * 
 */
CT_EditorMain::CT_EditorMain()
{
	editorWindow = new CT_EditorWindows();
	grid = Engine::CreateEntity<CT_EditorGrid>();
	
	grid->SetupGrid(CameraManager::GetRenderingCamera());

	

}


/**
 * Standard destructor.
 * 
 */
CT_EditorMain::~CT_EditorMain()
{
	Engine::DestroyEntity(grid);
	delete(editorWindow);
}
/**
 * Renders the Editor windows.
 * 
 */

void CT_EditorMain::RenderWindows()
{
	editorWindow->render();
}
