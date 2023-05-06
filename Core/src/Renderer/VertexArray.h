#pragma once
#include "Base.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"

#include <memory>
#include <vector>

namespace DXR
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer, const Ref<Shader>& shader) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
		static Ref<VertexArray> Create();
	};
}