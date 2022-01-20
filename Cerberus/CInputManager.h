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
	static char* boolMem;
	static unsigned short memLengthBytes;

public:
	static unsigned short Init();
	static bool GetKeyState(Keys::InputKeys key);
	static void SetKeyState(Keys::InputKeys key, bool newState);
	static void Cleanup();

	static Vector3 mousePos;
};