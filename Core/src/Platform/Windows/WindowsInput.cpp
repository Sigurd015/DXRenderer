#include "pch.h"
#include "Input/Input.h"
#include "Core/Application.h"

namespace DXC
{
	bool Input::IsKeyPressed(const KeyCode key)
	{
		return GetAsyncKeyState(key) & 0x8000;
	}

	bool Input::IsMouseButtonPressed(const MouseCode button)
	{
		return GetAsyncKeyState(button) & 0x8000;
	}

	DirectX::XMFLOAT2 Input::GetMousePosition()
	{
		POINT point{ 0,0 };
		GetCursorPos(&point);
		ScreenToClient((HWND)Application::Get().GetWindow().GetNativeWindow(), &point);
		return { (float)point.x ,(float)point.y };
	}
}