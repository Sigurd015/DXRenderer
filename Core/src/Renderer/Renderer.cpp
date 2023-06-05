#include "pch.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Pipeline.h"

namespace DXR
{
	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::Shutdown()
	{}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(const Camera& camera, const DirectX::XMMATRIX& transform)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetProjection() * DirectX::XMMatrixInverse(nullptr, transform);
	}

	void Renderer::EndScene()
	{}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<Pipeline>& pipeline, const DirectX::XMMATRIX& transform)
	{
		shader->Bind();
		//shader->SetUniform("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		//shader->SetUniform("u_Transform", transform);

		RenderCommand::DrawIndexed(pipeline);
	}
}