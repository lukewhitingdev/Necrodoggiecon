/*******************************************************************
 * \file   CUIManager.cpp
 * \brief  static UI Manager class. Provides access to UI anywhere in the project.
 * 
 * \author Samuel Elliot Jackson
 * \date   May 2022
 *********************************************************************/
#include "Cerberus/Core/Utility/CUIManager.h"
#include "Cerberus/Core/UI/CWidget_Canvas.h"




std::map<std::string, class CWidget_Canvas*> CUIManager::activeCanvases;
std::vector<std::string> CUIManager::idList;


/**
 * Adds a new canvas to the application.
 * 
 * \param Canvas Custom canvas instance
 * \param ID ID of the canvas.
 * \return returns the created canvas.
 */
CWidget_Canvas* CUIManager::AddCanvas(CWidget_Canvas* Canvas, std::string ID)
{
	bool isNewCanvas = true;
	for (int i = 0; i < idList.size(); i++)
	{
		if (idList[i] == ID)
		{
			if (activeCanvases[idList[i]] != nullptr)
			{
				// Delete Canvas, might crash?
				Engine::DestroyEntity(activeCanvases[idList[i]]);
				activeCanvases[idList[i]] = Canvas;
				isNewCanvas = false;
				
			}
		}
		
		
	}
	if (isNewCanvas)
	{
		idList.push_back(ID);
		activeCanvases.insert(std::pair<std::string, CWidget_Canvas*>(ID, Canvas));
	}
	
	return Canvas;
}

/**
 * Hides all canvases loaded..
 * 
 */
void CUIManager::HideAllCanvases()
{
	for (int i = 0; i < idList.size(); i++)
	{
		if (activeCanvases[idList[i]] != nullptr)
		{
			activeCanvases[idList[i]]->SetVisibility(false);
			
		}
	}
}

/**
 * Gets a canvas by ID.
 * 
 * \param ID The ID to search for
 * \return returns the located canvas, will return null if none were found.
 */
CWidget_Canvas* CUIManager::GetCanvas(std::string ID)
{
	for (int i = 0; i < idList.size(); i++)
	{
		if (idList[i] == ID)
		{

			return activeCanvases[ID];
		}
	}
	return nullptr;
}
/**
 * Resets the manager and removes all canvas instances..
 * 
 */
void CUIManager::ClearAllCanvases()
{
	for (int i = 0; i < idList.size(); i++)
	{
		if (activeCanvases[idList[i]] != nullptr)
		{
			activeCanvases[idList[i]]->RemoveAllChildren();
			Engine::DestroyEntity(activeCanvases[idList[i]]);
		}
	}
	idList.clear();
	activeCanvases.clear();
}
/**
 * Updates all widget origins.
 * 
 * \param Pos The pos to update to.
 */

void CUIManager::UpdateUIOrigin(Vector3 Pos)
{
	for (int i = 0; i < idList.size(); i++)
	{
		if (activeCanvases[idList[i]] != nullptr)
		{
			activeCanvases[idList[i]]->UpdateWidgetOrigin(Pos);
			
		}
	}
}

