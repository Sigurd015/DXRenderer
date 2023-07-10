#pragma once
#include "MouseCodes.h"
#include "KeyCodes.h"

#include <DirectXMath.h>

namespace DXC
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);
		static DirectX::XMFLOAT2 GetMousePosition();
	};
}