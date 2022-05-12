#include "CameraManager.h"
#include "Cerberus\Core\Utility\DebugOutput\Debug.h"
std::map<std::uintptr_t,CCameraComponent*> CameraManager::cameras;
std::uintptr_t CameraManager::renderingCamera;

void CameraManager::AddCamera(CCameraComponent* camera)
{
	cameras.emplace(std::make_pair((uintptr_t)camera, camera));
}

void CameraManager::RemoveCamera(CCameraComponent* camera)
{
	if(cameras.find((uintptr_t)camera) != cameras.end())
	{
		cameras.erase((uintptr_t)camera);

		if((uintptr_t)camera == renderingCamera)
		{
			if(cameras.size() > 0)
			{
				std::map<std::uintptr_t, CCameraComponent*>::iterator it = cameras.begin();
				renderingCamera = it->first;
			}
			else
			{
				Debug::LogError("Removed the last camera in the manager. No Rendering Camera exists now!.");
			}
		}
	}
	else
	{
		Debug::LogError("Tried to remove a camera that doesnt exist.");
		return;
	}
}

CCameraComponent* CameraManager::GetRenderingCamera()
{
	if(cameras.find(renderingCamera) != cameras.end())
	{
		return cameras.at(renderingCamera);
	}

	Debug::LogError("Tried to get rendering camera when it has not been set.");
	return nullptr;
}

void CameraManager::SetRenderingCamera(CCameraComponent* camera)
{
	if(cameras.find((uintptr_t)camera) != cameras.end())
	{
		renderingCamera = (uintptr_t)camera;
	}
	else
	{
		Debug::LogError("Tried to set rendering camera when it does not exist within the camera manager.");
		return;
	}
}

std::vector<CCameraComponent*> CameraManager::GetAllCameras()
{
	std::vector<CCameraComponent*> vec;

	for(const auto& cam : cameras)
	{
		vec.push_back(cam.second);
	}

	return vec;
}
