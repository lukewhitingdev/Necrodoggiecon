/*****************************************************************//**
 * \file   Math.h
 * \brief  Utility Math Class
 * 
 * \author everyone
 * \date   May 2022
 *********************************************************************/

#pragma once
#include <random>

class Math
{
public:
	static int random(int min, int max)
	{
		return rand() % ((max - min) + 1) + min;
	}
};