/*****************************************************************//**
 * \file   Debug.cpp
 * \brief  Allows for debug logging to a in-game console using IMGUI.
 * 
 * \author Luke Whiting
 * \date   Jan 2022
 *********************************************************************/
#include "Cerberus/Core/Utility/DebugOutput/Debug.h"
DebugOutput* Debug::output = nullptr;
int Debug::logSize = 1000;