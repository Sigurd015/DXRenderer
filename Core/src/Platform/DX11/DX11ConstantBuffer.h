#pragma once
#include "Renderer/ConstantBuffer.h"

#include <d3d11.h>
#include <Windows.h>
#include <wrl.h>

namespace DXC
{
	class DX11ConstantBuffer : public ConstantBuffer
	{
	public:
		DX11ConstantBuffer(uint32_t size, uint32_t binding);
		virtual ~DX11ConstantBuffer();
		virtual void Bind() override;
		virtual void SetData(const void* data, uint32_t offset = 0) override;
	private:
		uint32_t m_DataSize;
		uint32_t m_BindingID;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_ConstantBuffer;
	};
}