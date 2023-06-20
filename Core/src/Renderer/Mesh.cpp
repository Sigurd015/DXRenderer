#include "pch.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace DXR
{
	Mesh::Mesh(const std::string& filename)
	{
		Assimp::Importer importer;
		auto pAssimpScene = importer.ReadFile("assets/models/" + filename,
			aiProcess_Triangulate |
			aiProcess_SortByPType |
			aiProcess_JoinIdenticalVertices |
			aiProcess_GenNormals |
			aiProcess_GenUVCoords
		);

		if (pAssimpScene && !(pAssimpScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && pAssimpScene->HasMeshes())
		{
			auto pMesh = pAssimpScene->mMeshes[0];
			uint32_t numVertices = pMesh->mNumVertices;
			for (uint32_t i = 0; i < numVertices; ++i)
			{
				aiVector3D vertex = pMesh->mVertices[i];
				aiVector3D normal = pMesh->mNormals[i];
				aiVector3D texCoord = pMesh->mTextureCoords[0][i];
				m_Vertices.push_back({
					{vertex.x, vertex.y, vertex.z},
					{normal.x, normal.y, normal.z},
					{texCoord.x, texCoord.y}
					});
			}

			uint32_t numIndices = pMesh->mNumFaces;
			for (uint32_t i = 0; i < numIndices; ++i)
			{
				const auto& face = pMesh->mFaces[i];
				m_Indices.push_back({ face.mIndices[0],face.mIndices[1],face.mIndices[2] });
			}

			importer.FreeScene();
			Load();
		}
	}

	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<Index>& indices) : m_Vertices(vertices), m_Indices(indices)
	{
		Load();
	}

	Mesh::Mesh(const Ref<Mesh>& other)
	{
		m_Vertices = other->m_Vertices;
		m_Indices = other->m_Indices;
		Load();
	}

	void Mesh::Update(const DirectX::XMMATRIX& transform)
	{
		//TODO: Why can't update vertices at CPU side? or is this function not correct?
		/*for (auto& vertex : m_Vertices)
		{
			DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&vertex.Position);
			DirectX::XMVECTOR normal = DirectX::XMLoadFloat3(&vertex.Normal);
			position = DirectX::XMVector3Transform(position, transform);
			normal = DirectX::XMVector3TransformNormal(normal, transform);

			DirectX::XMStoreFloat3(&vertex.Position, position);
			DirectX::XMStoreFloat3(&vertex.Normal, normal);
		}
		m_VertexBuffer->SetData(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex));*/
	}

	void Mesh::Load()
	{
		m_VertexBuffer = VertexBuffer::Create(m_Vertices.size() * sizeof(Vertex));
		m_VertexBuffer->SetData(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex));
		m_IndexBuffer = IndexBuffer::Create(m_Indices.data(), m_Indices.size() * sizeof(Index));

		//TODO: Make layout dynamic
		DXR::VertexBufferLayout layout = {
		   { DXR::ShaderDataType::Float3, "a_Position" },
		   { DXR::ShaderDataType::Float3, "a_Normal" },
		   { DXR::ShaderDataType::Float2, "a_TexCoord" },
		};
		m_VertexBuffer->SetLayout(layout);
	}
}