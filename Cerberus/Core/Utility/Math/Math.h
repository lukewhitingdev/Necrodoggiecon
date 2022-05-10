/*****************************************************************//**
 * \file   Math.h
 * \brief  Utility Math Class
 * 
 * \author Everyone
 * \date   May 2022
 *********************************************************************/

#pragma once
#include <random>
#include "Cerberus/Core/Engine.h"
#include "Cerberus/Core/Structs/CCamera.h"

/**
 * Class of all the static maths functions that don't fit into existing classes.
 */
class Math
{
public:
	static int random(int min, int max)
	{
		return rand() % ((max - min) + 1) + min;
	}

	/**
	 * Convert screen coords to world space.
	 * Useful for converting the mouse to world space.
	 * 
	 * \param vec vector to be converted to world space.
	 * \return 
	 */
	static XMFLOAT3 FromScreenToWorld(const XMFLOAT3& vec)
	{
		XMFLOAT3 newVec = XMFLOAT3((vec.x * 1 / Engine::camera.GetZoom() + Engine::camera.GetCameraPosition().x), (vec.y * 1 / Engine::camera.GetZoom() + Engine::camera.GetCameraPosition().y), vec.z);
		return newVec;
	}
};