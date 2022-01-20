#include "CInputManager.h"
#include <cmath>
#include "Engine.h"

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
	return (keyStates[int(floor(int(key) / 8.0f))] >> key % 8) & 1;	//Get bit value at key location in keyStates array
}

void Input::SetKeyState(Keys::InputKeys key, bool newState)
{
	if(newState)
		keyStates[int(floor(int(key) / 8.0f))] |= 1 << key % 8;	//Set bit value to 1 at key location in keyStates array
	else
		keyStates[int(floor(int(key) / 8.0f))] &= ~(1 << key % 8);	//Set bit value to 0 at key location in keyStates array
}

void Input::UpdateKeys(const unsigned int& wParam, bool newState)
{
	if (wParam == 0x57) { Input::SetKeyState(Keys::W, newState); return; }
	if (wParam == 0x41) { Input::SetKeyState(Keys::A, newState); return; }
	if (wParam == 0x53) { Input::SetKeyState(Keys::S, newState); return; }
	if (wParam == 0x44) { Input::SetKeyState(Keys::D, newState); return; }
	if (wParam == 0x45) { Input::SetKeyState(Keys::E, newState); return; }
	if (wParam == 0x46) { Input::SetKeyState(Keys::F, newState); return; }
	if (wParam == 0x52) { Input::SetKeyState(Keys::R, newState); return; }
	if (wParam == 0x31) { Input::SetKeyState(Keys::One, newState); return; }
	if (wParam == 0x32) { Input::SetKeyState(Keys::Two, newState); return; }
	if (wParam == 0x33) { Input::SetKeyState(Keys::Three, newState); return; }
	if (wParam == VK_SPACE) { Input::SetKeyState(Keys::Space, newState); return; }
	if (wParam == VK_SHIFT) { Input::SetKeyState(Keys::Shift, newState); return; }
	if (wParam == VK_ESCAPE) { Input::SetKeyState(Keys::Esc, newState); return; }
	if (wParam == VK_F1) { Input::SetKeyState(Keys::F1, newState); return; }
}
