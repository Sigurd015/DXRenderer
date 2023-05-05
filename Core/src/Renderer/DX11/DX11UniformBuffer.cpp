#include "pch.h"
#include "Renderer/DX11/DX11UniformBuffer.h"
#include "Renderer/DX11/DX11Context.h"

namespace DXR
{
	DX11UniformBuffer::DX11UniformBuffer(uint32_t size, uint32_t binding) :m_BindingID(binding)
	{
		m_Buffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		m_Buffer.Usage = D3D11_USAGE_DYNAMIC;
		m_Buffer.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		m_Buffer.MiscFlags = 0;
		m_Buffer.ByteWidth = size;
		m_Buffer.StructureByteStride = 0;
	}

	DX11UniformBuffer::~DX11UniformBuffer()
	{

	}

	void DX11UniformBuffer::SetData(const void* data, uint32_t size, uint32_t offset)
	{
		D3D11_SUBRESOURCE_DATA resourceData = {};
		resourceData.pSysMem = &data;
		DX11Context::GetDevice()->CreateBuffer(&m_Buffer, &resourceData, &m_ConstantBuffer);
	}
}