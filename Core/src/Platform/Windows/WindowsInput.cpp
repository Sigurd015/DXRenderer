#include "pch.h"
#include "Input/Input.h"
#include "Engine/Application.h"

namespace DXR
{
	bool Input::IsKeyPressed(const KeyCode key)
	{
		return GetKeyState(key) & 0x8000;
	}

	bool Input::IsMouseButtonPressed(const MouseCode button)
	{
		return GetKeyState(button) & 0x8000;
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		POINT point{ 0,0 };
		GetCursorPos(&point);
		ScreenToClient((HWND)Application::Get().GetWindow().GetNativeWindow(), &point);
		return { point.x,point.y };
	}
}