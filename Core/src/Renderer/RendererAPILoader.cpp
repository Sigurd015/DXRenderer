#include "pch.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Buffer.h"
#include "Renderer/UniformBuffer.h"
#include "Renderer/Shader.h"
#include "Renderer/RenderingContext.h"
#include "Renderer/RendererAPI.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/DX11/DX11Context.h"
#include "Renderer/DX11/DX11API.h"
#include "Renderer/DX11/DX11VertexArray.h"
#include "Renderer/DX11/DX11Buffer.h"
#include "Renderer/DX11/DX11Shader.h"
#include "Renderer/DX11/DX11UniformBuffer.h"

namespace DXR
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

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

	Scope<RenderingContext> RenderingContext::Create(void* window)
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

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::DX11:
			return CreateRef<DX11Shader>(filepath);
			return nullptr;
		}
		return nullptr;
	}

	Ref<VertexArray> VertexArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::DX11:
			return CreateRef<DX11VertexArray>();
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
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
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

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
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

	//Ref<Texture2D> Texture2D::Create(const std::string& path)
	//{
	//	switch (RendererAPI::GetAPI())
	//	{
	//	case RendererAPI::API::None:    HNB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	//	case RendererAPI::API::OpenGL:  return  CreateRef<OpenGLTexture2D>(path);
	//	}
	//	HNB_CORE_ASSERT(false, "Unknown RendererAPI!");
	//	return nullptr;
	//}

	//Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	//{
	//	switch (RendererAPI::GetAPI())
	//	{
	//	case RendererAPI::API::None:    HNB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	//	case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(width, height);
	//	}
	//	HNB_CORE_ASSERT(false, "Unknown RendererAPI!");
	//	return nullptr;
	//}

	//Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	//{
	//	switch (RendererAPI::GetAPI())
	//	{
	//	case RendererAPI::API::None:    HNB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	//	case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
	//	}

	//	HNB_CORE_ASSERT(false, "Unknown RendererAPI!");
	//	return nullptr;
	//}

	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:    
			return nullptr;
		case RendererAPI::API::DX11:  
			return CreateRef<DX11UniformBuffer>(size, binding);
		}

		return nullptr;
	}
}