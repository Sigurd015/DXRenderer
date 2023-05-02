#include "pch.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"

namespace DXR
{
//	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init()
	{
		RenderCommand::Init();
		//Renderer2D::Init();
	}

	void Renderer::Shutdown()
	{
		//Renderer2D::Shutdown();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	//void Renderer::BeginScene(const Camera& camera, const glm::mat4& transform)
	//{
	//	s_SceneData->ViewProjectionMatrix = camera.GetProjection() * glm::inverse(transform);
	//}

	void Renderer::EndScene()
	{}

	//void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	//{
	//	shader->Bind();
	//	shader->SetUniform("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
	//	shader->SetUniform("u_Transform", transform);

	//	vertexArray->Bind();
	//	RenderCommand::DrawIndexed(vertexArray);
	//}
}