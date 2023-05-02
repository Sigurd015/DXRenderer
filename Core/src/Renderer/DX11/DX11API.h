#pragma once
#include "Renderer/RendererAPI.h"

namespace DXR
{
	class DX11RendererAPI : public RendererAPI
	{
	public:
		void Init() override;
		void SetClearColor(float r, float g, float b, float a) override;
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		void Clear() override;
		/*void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
		void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) override;
		void SetLineWidth(float width) override;*/
	};
}