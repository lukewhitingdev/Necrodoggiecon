#include "Math.h"

#include <random>
#include "Cerberus/Core/Engine.h"
#include "Cerberus/Core/Structs/CCamera.h"
#include <sstream>

int Math::random(int min, int max)
{
	return rand() % ((max - min) + 1) + min;
}

XMFLOAT3 Math::FromScreenToWorld(const XMFLOAT3& vec)
{
	XMFLOAT3 newVec = XMFLOAT3((vec.x * 1 / Engine::camera.GetZoom() + Engine::camera.GetCameraPosition().x), (vec.y * 1 / Engine::camera.GetZoom() + Engine::camera.GetCameraPosition().y), vec.z);
	return newVec;
}

std::string Math::FloatToStringWithDigits(const float& number, const unsigned char numberOfDecimalPlaces, const bool preserveDecimalZeros, const unsigned char numberOfIntegralPlacesZeros)
{
	std::stringstream ss;
	ss << float(round(number * pow(10, numberOfDecimalPlaces))) / pow(10, numberOfDecimalPlaces);

	//TODO

	return ss.str();
}
