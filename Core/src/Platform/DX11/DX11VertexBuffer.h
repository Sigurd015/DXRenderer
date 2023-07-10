#pragma once
#include "Renderer/VertexBuffer.h"

#include <d3d11.h>
#include <wrl.h>

namespace DXC
{
	class DX11VertexBuffer : public VertexBuffer
	{
	public:
		DX11VertexBuffer(uint32_t size);
		DX11VertexBuffer::DX11VertexBuffer(const void* vertices, uint32_t size);
		~DX11VertexBuffer();
		void Bind() const override;
		void Unbind() const override;
		void SetData(const void* vertices, uint32_t size) override;
		const VertexBufferLayout& GetLayout() const override { return m_Layout; }
		void SetLayout(const VertexBufferLayout& layout)override { m_Layout = layout;	m_Stride = m_Layout.GetStride(); }
	private:
		uint32_t m_Stride = 0;
		VertexBufferLayout m_Layout;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
	};
}