#pragma once
#include "MouseCodes.h"
#include "KeyCodes.h"

namespace DXR
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
	};
}