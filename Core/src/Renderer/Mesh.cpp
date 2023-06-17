#include "pch.h"
#include "Mesh.h"

namespace DXR
{
	Mesh::Mesh(const std::string& filename)
	{}

	Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<Index>& indices)
	{
		m_VertexBuffer = VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(Vertex));
		m_IndexBuffer = IndexBuffer::Create(indices.data(), indices.size() * sizeof(Index));
	}
}