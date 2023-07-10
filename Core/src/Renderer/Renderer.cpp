#include "pch.h"
#include "Mesh.h"
#include "Renderer.h"
#include "RendererAPI.h"
#include "RenderCommandQueue.h"
#include "Pipeline.h"
#include "MeshFactory.h"
#include "Texture.h"

namespace DXC
{
	static Scope<RendererAPI> s_RendererAPI = RendererAPI::Create();
	struct RendererData
	{
		Ref<ShaderLibrary> ShaderLibrary;

		RenderCommandQueue* s_CommandQueue;

		std::unordered_map<std::string, Ref<Texture>> Textures;
		std::unordered_map<std::string, Ref<Mesh>> Meshes;
	};
	static RendererData* s_Data = nullptr;

	void Renderer::Init()
	{
		s_Data = new RendererData();
		s_Data->s_CommandQueue = new RenderCommandQueue();
		s_RendererAPI->Init();

		// Load default shaders
		s_Data->ShaderLibrary = CreateRef<ShaderLibrary>();
		s_Data->ShaderLibrary->Load("Phong");

		// Load default meshes
		//s_Data->Meshes["Box"] = MeshFactory::CreateBox({ 1.0f,1.0f,1.0f });

		// Load default textures
		Ref<Texture2D> whiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
		s_Data->Textures["White"] = whiteTexture;
	}

	void Renderer::Shutdown()
	{
		delete s_Data->s_CommandQueue;
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

	void Renderer::SubmitStaticMesh(const Ref<Mesh>& mesh, const Ref<Material>& material, const Ref<Pipeline>& pipeline, void* constantData)
	{
		Renderer::Submit([mesh, material, pipeline, constantData]()
			{
				s_RendererAPI->SubmitStaticMesh(mesh, material, pipeline, constantData);
			});
	}

	void Renderer::WaitAndRender()
	{
		s_Data->s_CommandQueue->Execute();
	}

	RenderCommandQueue& Renderer::GetRenderCommandQueue()
	{
		return *s_Data->s_CommandQueue;
	}

	Ref<Shader> Renderer::GetShader(const std::string& name)
	{
		return s_Data->ShaderLibrary->Get(name);
	}

	Ref<Mesh> Renderer::GetMesh(const std::string& name)
	{
		if (s_Data->Meshes.find(name) == s_Data->Meshes.end())
			return nullptr;

		return s_Data->Meshes[name];
	}

	Ref<Texture> Renderer::GetTexture(const std::string& name)
	{
		if (s_Data->Textures.find(name) == s_Data->Textures.end())
			return nullptr;

		return s_Data->Textures[name];
	}
}