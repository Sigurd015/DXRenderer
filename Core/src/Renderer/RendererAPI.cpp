#include "pch.h"
#include "Pipeline.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Shader.h"
#include "RendererContext.h"
#include "RendererAPI.h"
#include "Framebuffer.h"
#include "RenderPass.h"
#include "Platform/DX11/DX11Context.h"
#include "Platform/DX11/DX11API.h"
#include "Platform/DX11/DX11Pipeline.h"
#include "Platform/DX11/DX11VertexBuffer.h"
#include "Platform/DX11/DX11IndexBuffer.h"
#include "Platform/DX11/DX11Shader.h"
#include "Platform/DX11/DX11ConstantBuffer.h"
#include "Platform/DX11/DX11Texture.h"
#include "Platform/DX11/DX11Framebuffer.h"

namespace DXR
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::DX11;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::None:   return nullptr;
		case RendererAPI::API::DX11:  return CreateScope<DX11RendererAPI>();
		}

		return nullptr;
	}

	Ref<RenderPass> RenderPass::Create(const RenderPassSpecification& spec)
	{
		return CreateRef<RenderPass>(spec);
	}

	Ref<Pipeline> Pipeline::Create(const PipelineSpecification& spec)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::DX11:
			return CreateRef<DX11Pipeline>(spec);
		}
		return nullptr;
	}

	Scope<RendererContext> RendererContext::Create(void* window)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::DX11:
			return CreateScope<DX11Context>(static_cast<HWND*>(window));
		}

		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::DX11:
			return CreateRef<DX11Shader>(name);
		}
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::DX11:
			return CreateRef<DX11VertexBuffer>(size);
		}
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(const void* vertices, uint32_t size)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::DX11:
			return CreateRef<DX11VertexBuffer>(vertices, size);
		}
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(void* indices, uint32_t count)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::DX11:
			return CreateRef<DX11IndexBuffer>(indices, count);
		}
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::DX11:
			return  CreateRef<DX11Texture2D>(path);
		}
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::DX11:
			return CreateRef<DX11Texture2D>(width, height);
		}
		return nullptr;
	}

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::DX11:
			return CreateRef<DX11Framebuffer>(spec);
		}
		return nullptr;
	}

	Ref<ConstantBuffer> ConstantBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::DX11:
			return CreateRef<DX11ConstantBuffer>(size, binding);
		}

		return nullptr;
	}
}