#pragma once
#include "Renderer/VertexBuffer.h"

#include <d3d11.h>
#include <wrl.h>

namespace DXR
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
	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
	};
}