#include "pch.h"
#include "Renderer/DX11/DX11Buffer.h"
#include "Renderer/DX11/DX11Context.h"

namespace DXR
{
	//-------------
	// VertexBuffer 
	//-------------

	DX11VertexBuffer::DX11VertexBuffer(uint32_t size)
	{
		D3D11_BUFFER_DESC bufferDesc = { 0 };
		bufferDesc.ByteWidth = size;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = m_Stride;
		DXR_ASSERT(DX11Context::GetDevice()->CreateBuffer(&bufferDesc, nullptr, &m_VertexBuffer));
	}

	DX11VertexBuffer::DX11VertexBuffer(float* vertices, uint32_t size) 
	{
		D3D11_BUFFER_DESC bufferDesc = { 0 };
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.ByteWidth = size;
		bufferDesc.StructureByteStride = m_Stride;
		D3D11_SUBRESOURCE_DATA resourceData = {};
		resourceData.pSysMem = vertices;

		DXR_ASSERT(DX11Context::GetDevice()->CreateBuffer(&bufferDesc, &resourceData, &m_VertexBuffer));
	}

	DX11VertexBuffer::~DX11VertexBuffer()
	{

	}

	void DX11VertexBuffer::Bind() const
	{
		const UINT offset = 0;
		DX11Context::GetDeviceContext()->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &m_Stride, &offset);
	}

	void DX11VertexBuffer::Unbind() const
	{

	}

	void DX11VertexBuffer::SetData(const void* data, uint32_t size)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));
		DX11Context::GetDeviceContext()->Map(m_VertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy(mappedResource.pData, data, size);
		DX11Context::GetDeviceContext()->Unmap(m_VertexBuffer.Get(), 0);
	}

	//-------------
	// IndexBuffer 
	//-------------

	DX11IndexBuffer::DX11IndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count)
	{
		D3D11_BUFFER_DESC buffer = {};
		buffer.BindFlags = D3D11_BIND_INDEX_BUFFER;
		buffer.Usage = D3D11_USAGE_DEFAULT;
		buffer.CPUAccessFlags = 0;
		buffer.MiscFlags = 0;
		buffer.ByteWidth = count * sizeof(uint32_t);
		buffer.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA resourceData = {};
		resourceData.pSysMem = indices;
		DX11Context::GetDevice()->CreateBuffer(&buffer, &resourceData, &m_IndexBuffer);
	}

	DX11IndexBuffer::~DX11IndexBuffer()
	{

	}

	void DX11IndexBuffer::Bind() const
	{
		DX11Context::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}

	void DX11IndexBuffer::Unbind() const
	{

	}

}