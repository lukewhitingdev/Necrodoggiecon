/*******************************************************************
 * \file   CWorld_Menu.cpp
 * \brief  
 * 
 * \author Samuel Elliot Jackson
 * \date   May 2022
 *********************************************************************/
#include "CWorld_Menu.h"
#include "Cerberus/Core/Utility/CUIManager.h"
#include "Necrodoggiecon/MainMenu.h"


/**
 * Sets up the world, in this case, loads the main menu canvas.
 * 
 */
void CWorld_Menu::SetupWorld()
{
	CUIManager::AddCanvas(Engine::CreateEntity<MainMenu>(), "MainMenu");
}
