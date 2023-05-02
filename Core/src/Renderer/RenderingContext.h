#pragma once

namespace DXR
{
	class RenderingContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;
		static Scope<RenderingContext> Create(void* window);
	};
}