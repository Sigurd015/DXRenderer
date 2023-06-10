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

	void Renderer::BeginRender(Ref<Pipeline> pipeline)
	{
		s_RendererAPI->BeginRender(pipeline);
	}

	void Renderer::EndRender()
	{
		s_RendererAPI->EndRender();
	}

	void Renderer::SubmitStaticMesh(Ref<Mesh>& mesh, Ref<Pipeline>& pipeLine, const DirectX::XMMATRIX& transform)
	{
		s_RendererAPI->SubmitStaticMesh(mesh, pipeLine, transform);
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