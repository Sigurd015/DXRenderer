#include "pch.h"
#include "Renderer/DX11/DX11VertexArray.h"
#include "Renderer/DX11/DX11Shader.h"
#include "Renderer/DX11/DX11Context.h"

#include <vector>
#include <d3d11.h>

namespace DXR
{
	static DXGI_FORMAT ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return DXGI_FORMAT_R32G32_FLOAT;
		case ShaderDataType::Float2:   return DXGI_FORMAT_R32G32_FLOAT;
		case ShaderDataType::Float3:   return DXGI_FORMAT_R32G32_FLOAT;
		case ShaderDataType::Float4:   return DXGI_FORMAT_R32G32_FLOAT;
		case ShaderDataType::Mat3:     return DXGI_FORMAT_R32G32_FLOAT;
		case ShaderDataType::Mat4:     return DXGI_FORMAT_R32G32_FLOAT;
		case ShaderDataType::Int:      return DXGI_FORMAT_R32_UINT;
		case ShaderDataType::Int2:     return DXGI_FORMAT_R32_UINT;
		case ShaderDataType::Int3:     return DXGI_FORMAT_R32_UINT;
		case ShaderDataType::Int4:     return DXGI_FORMAT_R32_UINT;
		}
		return DXGI_FORMAT_UNKNOWN;
	}

	DX11VertexArray::DX11VertexArray()
	{}

	DX11VertexArray::~DX11VertexArray()
	{}

	void DX11VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

	void DX11VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer, const Ref<Shader> shader)
	{
		vertexBuffer->Bind();
		DX11Shader* dx11shader = (DX11Shader*)shader.get();
		const auto& layout = vertexBuffer->GetLayout();
		D3D11_INPUT_ELEMENT_DESC inputDesc[2] = {};
		int index = 0;
		for (const auto& element : layout)
		{
			D3D11_INPUT_ELEMENT_DESC temp{};
			switch (element.Type)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			{
				temp.SemanticName = element.Name.c_str();
				temp.SemanticIndex = 0;
				temp.Format = ShaderDataTypeToOpenGLBaseType(element.Type);
				temp.InputSlot = 0;
				temp.AlignedByteOffset = element.Offset;
				temp.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				temp.InstanceDataStepRate = 0;
				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Bool:
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				break;
			}
			default:
				break;
			}
			inputDesc[index++] = temp;
		}
		Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
		DXR_ASSERT(DX11Context::GetDevice()->CreateInputLayout(
			inputDesc, (UINT)std::size(inputDesc), dx11shader->GetVertextBufferPointer(),
			dx11shader->GetVertextBufferSize(), &inputLayout));
		DX11Context::GetDeviceContext()->IASetInputLayout(inputLayout.Get());
		DXR_INFO("BUffersize:", dx11shader->GetVertextBufferSize());
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void DX11VertexArray::Bind() const
	{

	}

	void DX11VertexArray::Unbind() const
	{

	}
}