#pragma once
#include "Core/Base.h"
#include "Renderer/Framebuffer.h"

namespace DXR
{
	struct RenderPassSpecification
	{
		Ref<Framebuffer> TargetFramebuffer;
	};

	class RenderPass
	{
	public:
		RenderPass(const RenderPassSpecification& spec) :m_Specification(spec) {}
		~RenderPass() = default;

		RenderPassSpecification& GetSpecification() { return m_Specification; }
		const RenderPassSpecification& GetSpecification() const { return m_Specification; }

		static Ref<RenderPass> Create(const RenderPassSpecification& spec);
	private:
		RenderPassSpecification m_Specification;
	};
}