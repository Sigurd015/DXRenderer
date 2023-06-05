#pragma once
#include "Renderer/Pipeline.h"

#include <d3d11.h>
#include <Windows.h>
#include <wrl.h>

namespace DXR
{
	class DX11Pipeline : public Pipeline
	{
	public:
		DX11Pipeline() = default;
		~DX11Pipeline() = default;
		void Bind() const override;
		void Unbind() const override;
		void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer, const Ref<Shader>& shader) override;
		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}