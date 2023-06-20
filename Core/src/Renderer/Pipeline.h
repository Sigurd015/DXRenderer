#pragma once
#include "Core/Base.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "RenderPass.h"

#include <memory>
#include <vector>

namespace DXR
{
	enum class PrimitiveTopology
	{
		None = 0,
		Points,
		Lines,
		Triangles,
	};

	struct PipelineSpecification
	{
		Ref<Shader> Shader;
		VertexBufferLayout Layout;
		Ref<RenderPass> RenderPass;
		PrimitiveTopology Topology = PrimitiveTopology::Triangles;
	};

	class Pipeline
	{
	public:
		virtual ~Pipeline() = default;
		virtual void Invalidate() = 0;
		virtual void Bind() = 0;

		virtual PipelineSpecification& GetSpecification() = 0;
		virtual const PipelineSpecification& GetSpecification() const = 0;

		virtual void SetConstantBuffer(const Ref<ConstantBuffer>& constantBuffer) = 0;
		virtual Ref<ConstantBuffer> GetConstantBuffer(uint32_t binding = 0) = 0;

		static Ref<Pipeline> Create(const PipelineSpecification& spec);
	};
}