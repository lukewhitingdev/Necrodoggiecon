#pragma once
#include "Vector3.h"

namespace Keys
{
	enum InputKeys
	{
		W, A, S, D, RMB, LMB, MMB, END_ENTRY
	};
}

class Input
{
	static char keyStates[Keys::InputKeys::END_ENTRY / 8 + 1];	//Get approximate size of InputKeys

public:
	static bool GetKeyState(Keys::InputKeys key);
	static void SetKeyState(Keys::InputKeys key, bool newState);

	static Vector3 mousePos;
};