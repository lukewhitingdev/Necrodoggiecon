/*****************************************************************//**
 * \file   Math.h
 * \brief  Utility Math Class
 * 
 * \author Everyone
 * \date   May 2022
 *********************************************************************/

#pragma once

#include "Cerberus/Core/Engine.h"

/**
 * Class of all the static maths functions that don't fit into existing classes.
 */
class Math
{
public:
	static int random(int min, int max);

	/**
	 * Convert screen coords to world space.
	 * Useful for converting the mouse to world space.
	 * 
	 * \param vec vector to be converted to world space.
	 * \param camera rendering camera.
	 * \return 
	 */
	static XMFLOAT3 FromScreenToWorld(const XMFLOAT3& vec, CCameraComponent* camera);

	/**
	 * unfinished right now.
	 * 
	 * \param number
	 * \param numberOfDecimalPlaces
	 * \param preserveDecimalZeros
	 * \param numberOfIntegralPlacesZeros
	 * \return 
	 */
	static std::string FloatToStringWithDigits(const float& number, const unsigned char numberOfDecimalPlaces = 3, const bool preserveDecimalZeros = false, const unsigned char numberOfIntegralPlacesZeros = 1);
};