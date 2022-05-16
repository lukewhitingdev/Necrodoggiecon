#pragma once
#include "Cerberus\Core\Utility\Vector3.h"

namespace Inputs
{
	class InputManager
	{
	public:

		enum Keys
		{
			A = 0,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z,
			Num0,
			Num1,
			Num2,
			Num3,
			Num4,
			Num5,
			Num6,
			Num7,
			Num8,
			Num9,
			Escape,
			LControl,
			LShift,
			LAlt,
			LWindows,
			RControl,
			RShift,
			RAlt,
			RWindows,
			Menu,
			LBracket,
			RBracket,
			Semicolon,
			Comma,
			Period,
			Slash,
			Backslash,
			Tilde,
			Equals,
			Minus,
			Space,
			Enter,
			Backspace,
			Tab,
			PageUp,
			PageDown,
			End,
			Home,
			Insert,
			Delete,
			Add,
			Subtract,
			Multiply,
			Divide,
			Left,
			Right,
			Up,
			Down,
			Numpad0,
			Numpad1,
			Numpad2,
			Numpad3,
			Numpad4,
			Numpad5,
			Numpad6,
			Numpad7,
			Numpad8,
			Numpad9,
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			COUNT
		};

		enum Mouse
		{
			LButton,
			RButton,
			MButton,
			MCOUNT
		};

		static Vector3 mousePos;

	

		static int keyCodes(Keys key);

		static int SetMouse(Mouse mouse);

		static bool IsKeyPressed(Keys key);

		static bool IsKeyPressedDown(Keys key);

		static bool IsKeyReleased(Keys key);

		static bool IsMouseButtonPressed(Mouse mouse);

		static bool IsMouseButtonPressedDown(Mouse mouse);

		static bool IsMouseButtonReleased(Mouse mouse);
	};

};