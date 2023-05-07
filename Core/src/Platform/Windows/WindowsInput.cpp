#include "pch.h"
#include "Input/Input.h"
#include "Engine/Application.h"

namespace DXR
{
	bool Input::IsKeyPressed(const KeyCode key)
	{
		return false;
	}
	bool Input::IsMouseButtonPressed(const MouseCode button)
	{
		return false;
	}
	std::pair<float, float> Input::GetMousePosition()
	{
		double x, y;
		return { x, y };
	}
}