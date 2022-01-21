#include "KeyboardInputs.h"
#include <windows.h>

namespace Inputs
{
	bool keyboardKeyStates[Inputs::KeyboardInputs::Keys::COUNT][1] =
	{
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false},
		{false}
	};

	bool mouseKeyStates[Inputs::KeyboardInputs::Mouse::MCOUNT][1] =
	{
		{false},
		{false},
		{false}
	};

	int KeyboardInputs::keyCodes(Keys key)
	{
		int Async = 0;
		switch (key)
		{
		default:
			Async = 0;
			break;
		case Keys::A:
			Async = 0x41;
			break;
		case Keys::B:
			Async = 0x42;
			break;
		case Keys::C:
			Async = 0x43;
			break;
		case Keys::D:
			Async = 0x44;
			break;
		case Keys::E:
			Async = 0x45;
			break;
		case Keys::F:
			Async = 0x46;
			break;
		case Keys::G:
			Async = 0x47;
			break;
		case Keys::H:
			Async = 0x48;
			break;
		case Keys::I:
			Async = 0x49;
			break;
		case Keys::J:
			Async = 0x4A;
			break;
		case Keys::K:
			Async = 0x4B;
			break;
		case Keys::L:
			Async = 0x4C;
			break;
		case Keys::M:
			Async = 0x4D;
			break;
		case Keys::N:
			Async = 0x4E;
			break;
		case Keys::O:
			Async = 0x4F;
			break;
		case Keys::P:
			Async = 0x50;
			break;
		case Keys::Q:
			Async = 0x51;
			break;
		case Keys::R:
			Async = 0x52;
			break;
		case Keys::S:
			Async = 0x53;
			break;
		case Keys::T:
			Async = 0x54;
			break;
		case Keys::U:
			Async = 0x55;
			break;
		case Keys::V:
			Async = 0x56;
			break;
		case Keys::W:
			Async = 0x57;
			break;
		case Keys::X:
			Async = 0x58;
			break;
		case Keys::Y:
			Async = 0x59;
			break;
		case Keys::Z:
			Async = 0x5A;
			break;
		case Keys::Num0:
			Async = 0x30;
			break;
		case Keys::Num1:
			Async = 0x31;
			break;
		case Keys::Num2:
			Async = 0x32;
			break;
		case Keys::Num3:
			Async = 0x33;
			break;
		case Keys::Num4:
			Async = 0x34;
			break;
		case Keys::Num5:
			Async = 0x35;
			break;
		case Keys::Num6:
			Async = 0x36;
			break;
		case Keys::Num7:
			Async = 0x37;
			break;
		case Keys::Num8:
			Async = 0x38;
			break;
		case Keys::Num9:
			Async = 0x39;
			break;
		case Keys::Escape:
			Async = 0x1B;
			break;
		case Keys::LControl:
			Async = 0xA2;
			break;
		case Keys::LShift:
			Async = 0xA0;
			break;
		case Keys::LAlt:
			Async = 0xA4;
			break;
		case Keys::LWindows:
			Async = 0x5B;
			break;
		case Keys::RControl:
			Async = 0xA3;
			break;
		case Keys::RShift:
			Async = 0xA1;
			break;
		case Keys::RAlt:
			Async = 0xA5;
			break;
		case Keys::RWindows:
			Async = 0x5C;
			break;
		case Keys::Menu:
			Async = 0x5D;
			break;
		case Keys::LBracket:
			Async = 0xDB;
			break;
		case Keys::RBracket:
			Async = 0xDD;
			break;
		case Keys::Semicolon:
			Async = 0xBA;
			break;
		case Keys::Comma:
			Async = 0xBC;
			break;
		case Keys::Period:
			Async = 0xBE;
			break;
		case Keys::Slash:
			Async = 0xBF;
			break;
		case Keys::Backslash:
			Async = 0xDC;
			break;
		case Keys::Tilde:
			Async = 0xC0;
			break;
		case Keys::Equals:
			Async = 0xBB;
			break;
		case Keys::Minus:
			Async = 0xBD;
			break;
		case Keys::Space:
			Async = 0x20;
			break;
		case Keys::Enter:
			Async = 0x0D;
			break;
		case Keys::Backspace:
			Async = 0x08;
			break;
		case Keys::Tab:
			Async = 0x09;
			break;
		case Keys::PageUp:
			Async = 0x21;
			break;
		case Keys::PageDown:
			Async = 0x22;
			break;
		case Keys::End:
			Async = 0x23;
			break;
		case Keys::Home:
			Async = 0x24;
			break;
		case Keys::Insert:
			Async = 0x2D;
			break;
		case Keys::Delete:
			Async = 0x2E;
			break;
		case Keys::Add:
			Async = 0x6B;
			break;
		case Keys::Subtract:
			Async = 0x6D;
			break;
		case Keys::Multiply:
			Async = 0x6A;
			break;
		case Keys::Divide:
			Async = 0x6F;
			break;
		case Keys::Left:
			Async = 0x25;
			break;
		case Keys::Right:
			Async = 0x27;
			break;
		case Keys::Up:
			Async = 0x26;
			break;
		case Keys::Down:
			Async = 0x28;
			break;
		case Keys::Numpad0:
			Async = 0x60;
			break;
		case Keys::Numpad1:
			Async = 0x61;
			break;
		case Keys::Numpad2:
			Async = 0x62;
			break;
		case Keys::Numpad3:
			Async = 0x63;
			break;
		case Keys::Numpad4:
			Async = 0x64;
			break;
		case Keys::Numpad5:
			Async = 0x65;
			break;
		case Keys::Numpad6:
			Async = 0x66;
			break;
		case Keys::Numpad7:
			Async = 0x67;
			break;
		case Keys::Numpad8:
			Async = 0x68;
			break;
		case Keys::Numpad9:
			Async = 0x69;
			break;
		case Keys::F1:
			Async = 0x70;
			break;
		case Keys::F2:
			Async = 0x71;
			break;
		case Keys::F3:
			Async = 0x72;
			break;
		case Keys::F4:
			Async = 0x73;
			break;
		case Keys::F5:
			Async = 0x74;
			break;
		case Keys::F6:
			Async = 0x75;
			break;
		case Keys::F7:
			Async = 0x76;
			break;
		case Keys::F8:
			Async = 0x77;
			break;
		case Keys::F9:
			Async = 0x78;
			break;
		case Keys::F10:
			Async = 0x79;
			break;
		case Keys::F11:
			Async = 0x7A;
			break;
		case Keys::F12:
			Async = 0x7B;
			break;
		}
		return Async;
	}


	int KeyboardInputs::SetMouse(Mouse mouse)
	{
		int Async = 0;
		switch (mouse)
		{
		case Mouse::LButton:
			Async = 0x01;
			break;
		case Mouse::RButton:
			Async = 0x02;
			break;
		case Mouse::MButton:
			Async = 0x04;
			break;
		}
		return Async;
	}


	bool KeyboardInputs::IsKeyPressed(Keys key)
	{
		if (GetAsyncKeyState(keyCodes(key)) & 0x8000)
			Inputs::keyboardKeyStates[key][0] = true;
		else
			Inputs::keyboardKeyStates[key][0] = false;

		return Inputs::keyboardKeyStates[key][0];
	}


	bool KeyboardInputs::IsKeyPressedDown(Keys key)
	{
		if (GetAsyncKeyState(keyCodes(key)) < 0)
		{
			if (Inputs::keyboardKeyStates[key][0] == false)
			{
				Inputs::keyboardKeyStates[key][0] = true;
				return Inputs::keyboardKeyStates[key][0];
			}
			else
				return false;
		}
		else
		{
			Inputs::keyboardKeyStates[key][0] = false;
			return false;
		}
	}


	bool KeyboardInputs::IsKeyReleased(Keys key)
	{
		if (GetAsyncKeyState(keyCodes(key)) < 0)
		{
			Inputs::keyboardKeyStates[key][0] = true;
			return false;
		}
		else
		{
			if (Inputs::keyboardKeyStates[key][0] == true)
			{
				Inputs::keyboardKeyStates[key][0] = false;
				return true;
			}
			else
			{
				return false;
			}
		}
	}


	bool KeyboardInputs::IsMouseButtonPressed(Mouse mouse)
	{
		if (GetAsyncKeyState(SetMouse(mouse)) & 0x8000)
			Inputs::mouseKeyStates[mouse][0] = true;
		else
			Inputs::mouseKeyStates[mouse][0] = false;
		return Inputs::mouseKeyStates[mouse][0];
	}

};