#pragma once
#include "Pipeline.h"
#include "RenderPass.h"
#include "Mesh.h"

#include <DirectXMath.h>

namespace DXC
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
		virtual void ResetToSwapChain() = 0;

		virtual void BeginPipeline(const Ref<RenderPass>& renderPass) = 0;
		virtual void EndPipeline(const Ref<RenderPass>& renderPass) = 0;

		virtual void SubmitStaticMesh(const Ref<Mesh>& mesh, const Ref<Material>& material, const Ref<Pipeline>& pipeline, void* constantData) = 0;

		static API GetAPI() { return s_API; }
		static Scope<RendererAPI> Create();
	private:
		static API s_API;
	};
}