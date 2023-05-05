#pragma once
#include "Renderer/UniformBuffer.h"

#include <d3d11.h>
#include <Windows.h>
#include <wrl.h>

namespace DXR
{
	class DX11UniformBuffer : public UniformBuffer
	{
	public:
		DX11UniformBuffer(uint32_t size, uint32_t binding);
		virtual ~DX11UniformBuffer();

		virtual void SetData(const void* data, uint32_t size, uint32_t offset = 0) override;
	private:
		uint32_t m_BindingID;
		D3D11_BUFFER_DESC m_Buffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_ConstantBuffer;
	};
}