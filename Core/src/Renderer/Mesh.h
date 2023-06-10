#pragma once
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"
#include "Material.h"
#include "Pipeline.h"

#include <DirectXMath.h>
#include <vector>

namespace DXR
{
	struct Vertex
	{
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT2 Texcoord;
	};

	struct Index
	{
		uint32_t V1, V2, V3;
	};

	class Mesh
	{
	public:
		Mesh(const std::string& filename);
		Mesh(std::vector<Vertex>& vertices, std::vector<Index>& indices);
		~Mesh() = default;

		void SetMaterial(Ref<Material> material) { m_Material = material; }
		const std::vector<Vertex>& GetVertices() const { return m_Vertices; }
		const std::vector<Index>& GetIndices() const { return m_Indices; }
		Ref<VertexBuffer> GetVertexBuffer() { return m_VertexBuffer; }
		Ref<IndexBuffer> GetIndexBuffer() { return m_IndexBuffer; }
		Ref<Material> GetMaterial() { return m_Material; }
	private:
		Ref<Material> m_Material;
		std::vector<Vertex> m_Vertices;
		std::vector<Index> m_Indices;

		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}