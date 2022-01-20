#pragma once
#include "Vector3.h"

namespace Keys
{
	enum InputKeys
	{
		W, A, S, D, E, F, R, One, Two, Three, Space, Shift, Esc, F1, RMB, LMB, MMB, END_ENTRY
	};
}

class Input
{
	static char keyStates[Keys::END_ENTRY / 8 + 1];	//Get approximate size of InputKeys

public:
	static bool GetKeyState(Keys::InputKeys key);
	static void SetKeyState(Keys::InputKeys key, bool newState);

	static Vector3 mousePos;
};