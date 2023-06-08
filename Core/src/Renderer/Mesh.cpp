#include "pch.h"
#include "Mesh.h"

namespace DXR
{
	Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<Index>& indices)
		: m_Vertices(vertices), m_Indices(indices)
	{
		Init();
	}

	void Mesh::Init()
	{
		m_VertexBuffer = VertexBuffer::Create(m_Vertices.size() * sizeof(Vertex));
		m_VertexBuffer->SetLayout({
		{ DXR::ShaderDataType::Float3, "Position" },
		{ DXR::ShaderDataType::Float3, "Normal" },
		{ DXR::ShaderDataType::Float2, "TexCoord" },
			});
		m_Shader = DXR::Shader::Create("TestShader");
		m_IndexBuffer = IndexBuffer::Create(&(m_Indices.data()->V1), m_Indices.size() * sizeof(Index));

		m_VertexBuffer->SetData(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex));
	}
}