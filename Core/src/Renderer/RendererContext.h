#pragma once
#include "Core/Base.h"

namespace DXC
{
	class RendererContext
	{
	public:
		virtual void SwapBuffer(bool VSync) = 0;
		static Scope<RendererContext> Create(void* window);
	};
}