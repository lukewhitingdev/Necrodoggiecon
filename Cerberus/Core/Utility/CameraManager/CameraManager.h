/*****************************************************************//**
 * \file   CameraManager.cpp
 * \brief  Manages the cameras in the engine.
 *
 * \author Luke Whiting
 * \date   May 2022
 *********************************************************************/

#pragma once
#include <map>
#include <vector>
#include "Cerberus\Core\Components\CCameraComponent.h"
class CameraManager
{
public:
	
	static void AddCamera(CCameraComponent* camera);
	static void RemoveCamera(CCameraComponent* camera);
	static CCameraComponent* GetRenderingCamera();
	static void SetRenderingCamera(CCameraComponent* camera);
	static std::vector<CCameraComponent*> GetAllCameras();

private:
	static std::map<std::uintptr_t,CCameraComponent*> cameras;
	static CCameraComponent* renderingCamera;
};

