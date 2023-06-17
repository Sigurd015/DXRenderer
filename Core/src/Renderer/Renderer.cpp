#include "pch.h"
#include "Mesh.h"
#include "Renderer.h"
#include "RendererAPI.h"
#include "RenderCommandQueue.h"
#include "Pipeline.h"

namespace DXR
{
	static RenderCommandQueue* s_CommandQueue = nullptr;
	static Scope<RendererAPI> s_RendererAPI = RendererAPI::Create();

	void Renderer::Init()
	{
		s_CommandQueue = new RenderCommandQueue();
		s_RendererAPI->Init();
	}

	void Renderer::Shutdown()
	{
		delete s_CommandQueue;
	}

	void Renderer::SetClearColor(const DirectX::XMFLOAT4& color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		s_RendererAPI->SetViewport(0, 0, width, height);
	}

	void Renderer::BeginRenderPass(const Ref<RenderPass>& renderPass)
	{
		Renderer::Submit([renderPass]()
			{
				s_RendererAPI->BeginPipeline(renderPass);
			});
	}

	void Renderer::EndRenderPass(const Ref<RenderPass>& renderPass)
	{
		Renderer::Submit([renderPass]()
			{
				s_RendererAPI->EndPipeline(renderPass);
			});
	}

	void Renderer::ResetToSwapChain()
	{
		s_RendererAPI->ResetToSwapChain();
	}

	void Renderer::SubmitStaticMesh(const Ref<Mesh>& mesh, const  Ref<Pipeline>& pipeline)
	{
		Renderer::Submit([mesh, pipeline]()
			{
				s_RendererAPI->SubmitStaticMesh(mesh, pipeline);
			});
	}

	void Renderer::WaitAndRender()
	{
		s_CommandQueue->Execute();
	}

	RenderCommandQueue& Renderer::GetRenderCommandQueue()
	{
		return *s_CommandQueue;
	}
}