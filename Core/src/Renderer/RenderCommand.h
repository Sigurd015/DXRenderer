#pragma once
#include "Renderer/RendererAPI.h"

#include <cstdint>

namespace DXR
{
	class RenderCommand
	{
	public:
		static void Init()
		{
			s_RendererAPI->Init();
		}

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		static void SetClearColor(const DirectX::XMFLOAT4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		static void Clear()
		{
			s_RendererAPI->Clear();
		}

		static void DrawIndexed(const Ref<Pipeline>& pipeline, uint32_t indexCount = 0)
		{
			s_RendererAPI->DrawIndexed(pipeline, indexCount);
		}

		static void DrawLines(const Ref<Pipeline>& pipeline, uint32_t vertexCount)
		{
			s_RendererAPI->DrawLines(pipeline, vertexCount);
		}
	private:
		static Scope<RendererAPI> s_RendererAPI;
	};
}