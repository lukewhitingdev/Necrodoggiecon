#include <map>
#include <string>
#include <vector>
#include "Cerberus/Core/Utility/Vector3.h"
#pragma once
class CUIManager
{
	static std::map<std::string, class CWidget_Canvas*> activeCanvases;
	static std::vector<std::string> idList;
public:



	static class CWidget_Canvas* AddCanvas(class CWidget_Canvas* Canvas, std::string ID);

	static void HideAllCanvases();

	static class CWidget_Canvas* GetCanvas(std::string ID);

	static void ClearAllCanvases();

	static void UpdateUIOrigin(Vector3 Pos);

	


};

