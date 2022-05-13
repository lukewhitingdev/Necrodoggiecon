#include "Math.h"

#include <random>
#include "Cerberus/Core/Engine.h"
#include "Cerberus/Core/Structs/CCamera.h"
#include "Cerberus/Core/Components/CCameraComponent.h"
#include "Cerberus\Core\Utility\CameraManager\CameraManager.h"
#include <sstream>

int Math::random(int min, int max)
{
	return rand() % ((max - min) + 1) + min;
}

XMFLOAT3 Math::FromScreenToWorld(const XMFLOAT3& vec)
{
	if (CameraManager::GetRenderingCamera() == nullptr)
		return XMFLOAT3(0, 0, 0);

	XMFLOAT3 newVec = XMFLOAT3((vec.x * 1 / CameraManager::GetRenderingCamera()->GetZoomLevel() + CameraManager::GetRenderingCamera()->GetPosition().x), (vec.y * 1 / CameraManager::GetRenderingCamera()->GetZoomLevel() + CameraManager::GetRenderingCamera()->GetPosition().y), vec.z);
	return newVec;
}

std::string Math::FloatToStringWithDigits(const float& number, const unsigned char numberOfDecimalPlaces, const bool preserveDecimalZeros, const unsigned char numberOfIntegralPlacesZeros)
{
	std::stringstream ss;
	ss << float(round(number * pow(10, numberOfDecimalPlaces))) / pow(10, numberOfDecimalPlaces);

	//TODO

	return ss.str();
}