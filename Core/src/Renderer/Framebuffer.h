#pragma once
#include "Core/Base.h"

#include <vector>
#include <DirectXMath.h>

namespace DXR
{
	enum class FramebufferTextureFormat
	{
		None = 0,

		// Color
		RGBA8F,

		RED8UI,

		// Depth/stencil
		DEPTH24STENCIL8,

		// Defaults
		MousePick = RED8UI,
		Depth = DEPTH24STENCIL8
	};

	struct FramebufferTextureSpecification
	{
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat format) : TextureFormat(format) {}

		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
		// TODO: filtering/wrap
	};

	struct FramebufferAttachmentSpecification
	{
		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments) : Attachments(attachments) {}

		std::vector<FramebufferTextureSpecification> Attachments;
	};
	struct FramebufferSpecification
	{
		uint32_t Width = 0, Height = 0;
		FramebufferAttachmentSpecification Attachments;
		uint32_t Samples = 1;
		DirectX::XMFLOAT4 ClearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		int MousePickClearValue = -1;
		float DepthClearValue = 1.0f;
		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void ClearAttachment() = 0;
		virtual void* GetColorAttachment(uint32_t attachmentIndex = 0) const = 0;
		virtual void* GetDepthAttachment() const = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;
		virtual const FramebufferSpecification& GetSpecification() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
	};
}