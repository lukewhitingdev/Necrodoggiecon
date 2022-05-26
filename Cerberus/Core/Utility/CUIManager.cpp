#include "Cerberus/Core/Utility/CUIManager.h"
#include "Cerberus/Core/UI/CWidget_Canvas.h"




std::map<std::string, class CWidget_Canvas*> CUIManager::activeCanvases;
std::vector<std::string> CUIManager::idList;



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

