#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
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
		Ref<VertexBuffer> GetVertexBuffer() { return m_VertexBuffer; }
		Ref<IndexBuffer> GetIndexBuffer() { return m_IndexBuffer; }
		Ref<Material> GetMaterial() { return m_Material; }
	private:
		Ref<Material> m_Material;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}