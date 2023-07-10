#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Material.h"
#include "Pipeline.h"

#include <DirectXMath.h>
#include <vector>

namespace DXC
{
	struct Vertex
	{
		DirectX::XMFLOAT3 Position;   //Vec3
		DirectX::XMFLOAT3 Normal;     //Vec3
		DirectX::XMFLOAT2 Texcoord;   //Vec2
	};

	struct Index
	{
		uint32_t V1, V2, V3;
	};

	class Mesh
	{
	public:
		Mesh(const std::string& filename);
		Mesh(const std::vector<Vertex>& vertices, const std::vector<Index>& indices);
		Mesh(const Ref<Mesh>& other);
		~Mesh() = default;

		void Update(const DirectX::XMMATRIX& transform);
		Ref<VertexBuffer> GetVertexBuffer() { return m_VertexBuffer; }
		Ref<IndexBuffer> GetIndexBuffer() { return m_IndexBuffer; }
	private:
		void Load();
		std::vector<Vertex> m_Vertices;
		std::vector<Index> m_Indices;

		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}