#include "CInputManager.h"
#include <cmath>

char Input::keyStates[Keys::END_ENTRY / 8 + 1] = { 0 };
Vector3 Input::mousePos = { 0,0,0 };

/*
Basically, I want to store these booleans in as small of a memory footprint as possible.
bool type by default stores a single bool in 8 bits - meaning 7 wasted bits
So, I have created an array of bytes to access and use every single bit within the array to store the states
thats overall a potential 8x memory saving. :)
*/

bool Input::GetKeyState(Keys::InputKeys key)
{
	return (keyStates[int(floor(int(key) / 8.0f))] >> key % 8) & 1;
}

void Input::SetKeyState(Keys::InputKeys key, bool newState)
{
	if(newState)
		keyStates[int(floor(int(key) / 8.0f))] |= 1 << key % 8;
	else
		keyStates[int(floor(int(key) / 8.0f))] &= ~(1 << key % 8);
}
