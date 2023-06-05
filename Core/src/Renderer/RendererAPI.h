#pragma once
#include "Renderer/Pipeline.h"

#include <DirectXMath.h>

namespace DXR
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, DX11 = 1, DX12 = 2
		};
	public:
		virtual void Init() = 0;
		virtual void SetClearColor(const DirectX::XMFLOAT4& color) = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const Ref<Pipeline>& pipeline, uint32_t indexCount = 0) = 0;
		virtual void DrawLines(const Ref<Pipeline>& pipeline, uint32_t vertexCount) = 0;
		static API GetAPI() { return s_API; }
		static Scope<RendererAPI> Create();
	private:
		static API s_API;
	};
}