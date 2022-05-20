#include "Cerberus/Core/Utility/CUIManager.h"
#include "Cerberus/Core/UI/CWidget_Canvas.h"



std::map<std::string, class CWidget_Canvas*> CUIManager::activeCanvases;
std::vector<std::string> CUIManager::idList;



void CUIManager::AddCanvas(CWidget_Canvas* Canvas, std::string ID)
{
	idList.push_back(ID);
	activeCanvases.insert(std::pair<std::string, CWidget_Canvas*>(ID, Canvas));
}

CWidget_Canvas* CUIManager::GetCanvas(std::string ID)
{
	for (int i = 0; i < idList.size(); i++)
	{
		if (idList[i] == ID)
		{

			return activeCanvases["ID"];
		}
	}
	return nullptr;
}

void CUIManager::ClearAllCanvases()
{
	for (int i = 0; i < idList.size(); i++)
	{
		activeCanvases[idList[i]]->RemoveAllChildren();
		Engine::DestroyEntity(activeCanvases[idList[i]]);
	}
	idList.clear();
	activeCanvases.clear();
}

