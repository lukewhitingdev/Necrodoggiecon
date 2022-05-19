#include <map>
#include <string>
#include <vector>
#pragma once
class CUIManager
{
	static std::map<std::string, class CWidget_Canvas*> activeCanvases;
	static std::vector<std::string> idList;
public:

	static void Update(float deltaTime);

	static void AddCanvas(class CWidget_Canvas* Canvas, std::string ID);



	static void ClearAllCanvases();


};

