#include "CInputManager.h"
#include <cmath>
#include "Engine.h"

char* Input::boolMem = nullptr;
unsigned short Input::memLengthBytes = 0;
Vector3 Input::mousePos = { 0,0,0 };

/*
Basically, I want to store these booleans in as small of a memory footprint as possible.
bool type by default stores a single bool in 8 bits - meaning 7 wasted bits
So, I have created a section of contiguous memory to access and use every single bit to store the states
thats overall a potential 8x memory saving. :)
*/

unsigned short Input::Init()
{
	if (boolMem != nullptr)
	{
		Debug::Log("InputManager already init'd! Don't call the function again lmao.");
		Cleanup();
	}

	memLengthBytes = int(ceil((Keys::END_ENTRY + 1) / 8.0f));	//allocated the minimum amount of memory to store all the keys in the enum
	boolMem = (char*)malloc(memLengthBytes);
	memset(boolMem, 0, memLengthBytes);	//init to value of 0

	return memLengthBytes;
}

bool Input::GetKeyState(Keys::InputKeys key)
{
	return (*boolMem >> key) & 1;	//Get bit value at key location in boolMem
}

void Input::SetKeyState(Keys::InputKeys key, bool newState)
{
	if(newState)
		*boolMem |= 1 << key;	//Set bit value to 1 at key location in boolMem
	else
		*boolMem &= ~(1 << key);	//Set bit value to 0 at key location in boolMem
}

void Input::Cleanup()
{
	free(boolMem);
	memLengthBytes = 0;
}
