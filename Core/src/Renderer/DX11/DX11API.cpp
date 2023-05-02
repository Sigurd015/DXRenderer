#include "pch.h"
#include "Renderer/DX11/DX11API.h"
#include "Renderer/DX11/DX11Context.h"

namespace DXR
{
	void DX11RendererAPI::Init()
	{

	}

	void DX11RendererAPI::SetClearColor(float r, float g, float b, float a)
	{
		DX11Context::SetClearColor(r, g, b, a);
	}

	void DX11RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{

	}

	void DX11RendererAPI::Clear()
	{

	}
}