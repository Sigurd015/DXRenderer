#pragma once
#include "Renderer/VertexArray.h"

namespace DXR
{
	class DX11VertexArray : public VertexArray
	{
	public:
		DX11VertexArray();
		~DX11VertexArray();
		void Bind() const override;
		void Unbind() const override;
		void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer, const Ref<Shader>& shader = nullptr) override;
		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_VertexBufferIndex = 0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}