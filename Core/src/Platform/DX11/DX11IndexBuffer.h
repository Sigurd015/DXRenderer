#pragma once
#include "Renderer/IndexBuffer.h"

#include <d3d11.h>
#include <wrl.h>

namespace DXC
{
	class DX11IndexBuffer : public IndexBuffer
	{
	public:
		DX11IndexBuffer(void* indices, uint32_t count);
		~DX11IndexBuffer();
		void Bind() const override;
		void Unbind() const override;
		uint32_t GetCount() const { return m_Count; }
	private:
		uint32_t m_Count;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_IndexBuffer;
	};
}