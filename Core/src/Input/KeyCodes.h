#pragma once
#include <ostream>
#include <WinUser.h>

namespace DXR
{
	using KeyCode = uint16_t;

	namespace Key
	{
		enum : uint16_t
		{
			 /*case VK_TAB: return ImGuiKey_Tab;
			 case VK_LEFT: return ImGuiKey_LeftArrow;
			 case VK_RIGHT: return ImGuiKey_RightArrow;
			 case VK_UP: return ImGuiKey_UpArrow;
			 case VK_DOWN: return ImGuiKey_DownArrow;
			 case VK_PRIOR: return ImGuiKey_PageUp;
			 case VK_NEXT: return ImGuiKey_PageDown;
			 case VK_HOME: return ImGuiKey_Home;
			 case VK_END: return ImGuiKey_End;
			 case VK_INSERT: return ImGuiKey_Insert;
			 case VK_DELETE: return ImGuiKey_Delete;
			 case VK_BACK: return ImGuiKey_Backspace;
			 case VK_SPACE: return ImGuiKey_Space;
			 case VK_RETURN: return ImGuiKey_Enter;
			 case VK_ESCAPE: return ImGuiKey_Escape;
			 case VK_OEM_7: return ImGuiKey_Apostrophe;
			 case VK_OEM_COMMA: return ImGuiKey_Comma;
			 case VK_OEM_MINUS: return ImGuiKey_Minus;
			 case VK_OEM_PERIOD: return ImGuiKey_Period;
			 case VK_OEM_2: return ImGuiKey_Slash;
			 case VK_OEM_1: return ImGuiKey_Semicolon;
			 case VK_OEM_PLUS: return ImGuiKey_Equal;
			 case VK_OEM_4: return ImGuiKey_LeftBracket;
			 case VK_OEM_5: return ImGuiKey_Backslash;
			 case VK_OEM_6: return ImGuiKey_RightBracket;
			 case VK_OEM_3: return ImGuiKey_GraveAccent;
			 case VK_CAPITAL: return ImGuiKey_CapsLock;
			 case VK_SCROLL: return ImGuiKey_ScrollLock;
			 case VK_NUMLOCK: return ImGuiKey_NumLock;
			 case VK_SNAPSHOT: return ImGuiKey_PrintScreen;
			 case VK_PAUSE: return ImGuiKey_Pause;
			 case VK_NUMPAD0: return ImGuiKey_Keypad0;
			 case VK_NUMPAD1: return ImGuiKey_Keypad1;
			 case VK_NUMPAD2: return ImGuiKey_Keypad2;
			 case VK_NUMPAD3: return ImGuiKey_Keypad3;
			 case VK_NUMPAD4: return ImGuiKey_Keypad4;
			 case VK_NUMPAD5: return ImGuiKey_Keypad5;
			 case VK_NUMPAD6: return ImGuiKey_Keypad6;
			 case VK_NUMPAD7: return ImGuiKey_Keypad7;
			 case VK_NUMPAD8: return ImGuiKey_Keypad8;
			 case VK_NUMPAD9: return ImGuiKey_Keypad9;
			 case VK_DECIMAL: return ImGuiKey_KeypadDecimal;
			 case VK_DIVIDE: return ImGuiKey_KeypadDivide;
			 case VK_MULTIPLY: return ImGuiKey_KeypadMultiply;
			 case VK_SUBTRACT: return ImGuiKey_KeypadSubtract;
			 case VK_ADD: return ImGuiKey_KeypadAdd;
			 case IM_VK_KEYPAD_ENTER: return ImGuiKey_KeypadEnter;
			 case VK_LSHIFT: return ImGuiKey_LeftShift;
			 case VK_LCONTROL: return ImGuiKey_LeftCtrl;
			 case VK_LMENU: return ImGuiKey_LeftAlt;
			 case VK_LWIN: return ImGuiKey_LeftSuper;
			 case VK_RSHIFT: return ImGuiKey_RightShift;
			 case VK_RCONTROL: return ImGuiKey_RightCtrl;
			 case VK_RMENU: return ImGuiKey_RightAlt;
			 case VK_RWIN: return ImGuiKey_RightSuper;
			 case VK_APPS: return ImGuiKey_Menu;
			 case '0': return ImGuiKey_0;
			 case '1': return ImGuiKey_1;
			 case '2': return ImGuiKey_2;
			 case '3': return ImGuiKey_3;
			 case '4': return ImGuiKey_4;
			 case '5': return ImGuiKey_5;
			 case '6': return ImGuiKey_6;
			 case '7': return ImGuiKey_7;
			 case '8': return ImGuiKey_8;
			 case '9': return ImGuiKey_9;
			 case 'A': return ImGuiKey_A;
			 case 'B': return ImGuiKey_B;
			 case 'C': return ImGuiKey_C;
			 case 'D': return ImGuiKey_D;
			 case 'E': return ImGuiKey_E;
			 case 'F': return ImGuiKey_F;
			 case 'G': return ImGuiKey_G;
			 case 'H': return ImGuiKey_H;
			 case 'I': return ImGuiKey_I;
			 case 'J': return ImGuiKey_J;
			 case 'K': return ImGuiKey_K;
			 case 'L': return ImGuiKey_L;
			 case 'M': return ImGuiKey_M;
			 case 'N': return ImGuiKey_N;
			 case 'O': return ImGuiKey_O;
			 case 'P': return ImGuiKey_P;
			 case 'Q': return ImGuiKey_Q;
			 case 'R': return ImGuiKey_R;
			 case 'S': return ImGuiKey_S;
			 case 'T': return ImGuiKey_T;
			 case 'U': return ImGuiKey_U;
			 case 'V': return ImGuiKey_V;
			 case 'W': return ImGuiKey_W;
			 case 'X': return ImGuiKey_X;
			 case 'Y': return ImGuiKey_Y;
			 case 'Z': return ImGuiKey_Z;
			 case VK_F1: return ImGuiKey_F1;
			 case VK_F2: return ImGuiKey_F2;
			 case VK_F3: return ImGuiKey_F3;
			 case VK_F4: return ImGuiKey_F4;
			 case VK_F5: return ImGuiKey_F5;
			 case VK_F6: return ImGuiKey_F6;
			 case VK_F7: return ImGuiKey_F7;
			 case VK_F8: return ImGuiKey_F8;
			 case VK_F9: return ImGuiKey_F9;
			 case VK_F10: return ImGuiKey_F10;
			 case VK_F11: return ImGuiKey_F11;
			 case VK_F12: return ImGuiKey_F12;
			 //default: return ImGuiKey_None;*/

			Space = VK_SPACE,
			Apostrophe = 39, /* ' */
			Comma = 44, /* , */
			Minus = 45, /* - */
			Period = 46, /* . */
			Slash = 47, /* / */

			D0 = 48, /* 0 */
			D1 = 49, /* 1 */
			D2 = 50, /* 2 */
			D3 = 51, /* 3 */
			D4 = 52, /* 4 */
			D5 = 53, /* 5 */
			D6 = 54, /* 6 */
			D7 = 55, /* 7 */
			D8 = 56, /* 8 */
			D9 = 57, /* 9 */

			Semicolon = 59, /* ; */
			Equal = 61, /* = */

			A = 65,
			B = 66,
			C = 67,
			D = 68,
			E = 69,
			F = 70,
			G = 71,
			H = 72,
			I = 73,
			J = 74,
			K = 75,
			L = 76,
			M = 77,
			N = 78,
			O = 79,
			P = 80,
			Q = 81,
			R = 82,
			S = 83,
			T = 84,
			U = 85,
			V = 86,
			W = 87,
			X = 88,
			Y = 89,
			Z = 90,

			LeftBracket = 91,  /* [ */
			Backslash = 92,  /* \ */
			RightBracket = 93,  /* ] */
			GraveAccent = 96,  /* ` */

			World1 = 161, /* non-US #1 */
			World2 = 162, /* non-US #2 */

			/* Function keys */
			Escape = 256,
			Enter = 257,
			Tab = 258,
			Backspace = 259,
			Insert = 260,
			Delete = 261,
			Right = 262,
			Left = 263,
			Down = 264,
			Up = 265,
			PageUp = 266,
			PageDown = 267,
			Home = 268,
			End = 269,
			CapsLock = 280,
			ScrollLock = 281,
			NumLock = 282,
			PrintScreen = 283,
			Pause = 284,
			F1 = 290,
			F2 = 291,
			F3 = 292,
			F4 = 293,
			F5 = 294,
			F6 = 295,
			F7 = 296,
			F8 = 297,
			F9 = 298,
			F10 = 299,
			F11 = 300,
			F12 = 301,
			F13 = 302,
			F14 = 303,
			F15 = 304,
			F16 = 305,
			F17 = 306,
			F18 = 307,
			F19 = 308,
			F20 = 309,
			F21 = 310,
			F22 = 311,
			F23 = 312,
			F24 = 313,
			F25 = 314,

			/* Keypad */
			KP0 = 320,
			KP1 = 321,
			KP2 = 322,
			KP3 = 323,
			KP4 = 324,
			KP5 = 325,
			KP6 = 326,
			KP7 = 327,
			KP8 = 328,
			KP9 = 329,
			KPDecimal = 330,
			KPDivide = 331,
			KPMultiply = 332,
			KPSubtract = 333,
			KPAdd = 334,
			KPEnter = 335,
			KPEqual = 336,

			LeftShift = 340,
			LeftControl = 341,
			LeftAlt = 342,
			LeftSuper = 343,
			RightShift = 344,
			RightControl = 345,
			RightAlt = 346,
			RightSuper = 347,
			Menu = 348
		};
	}
}