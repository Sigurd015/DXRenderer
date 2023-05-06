#pragma once

namespace DXR
{
	class RenderingContext
	{
	public:
		virtual void SwapBuffer(bool VSync) = 0;
		static Scope<RenderingContext> Create(void* window);
	};
}