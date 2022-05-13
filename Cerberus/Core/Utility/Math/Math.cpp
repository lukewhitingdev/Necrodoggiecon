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
	bool isNegative = number < 0;

	unsigned int integerPart = floor(abs(number));
	unsigned int decimalPart = (abs(number) - integerPart) * pow(10, numberOfDecimalPlaces);

	std::string decimalPartString = std::to_string(decimalPart);

	if (preserveDecimalZeros && numberOfDecimalPlaces != decimalPartString.size())
	{
		for (int i = 0; i < int(numberOfDecimalPlaces) - int(decimalPartString.size()); i++)
		{
			decimalPartString.insert(decimalPartString.begin(), '0');
		}
	}

	std::string output = isNegative ? "-" : "";
	output.append(IntToString(integerPart, numberOfIntegralPlacesZeros));
	output.append(".");
	output.append(decimalPartString);
	
	return output;
}

std::string Math::IntToString(const int& number, const unsigned char numberOfIntegralPlacesZeros)
{
	bool isNegative = number < 0;

	std::string integerPartString = std::to_string(abs(number));

	if (numberOfIntegralPlacesZeros != integerPartString.size())
	{
		for (int i = 0; i < int(numberOfIntegralPlacesZeros) - int(integerPartString.size()); i++)
		{
			integerPartString.insert(integerPartString.begin(), '0');
		}
	}

	if(isNegative)
		integerPartString.insert(integerPartString.begin(), '-');

	return integerPartString;
}
