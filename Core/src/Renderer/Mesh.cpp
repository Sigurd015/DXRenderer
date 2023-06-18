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
			aiProcess_JoinIdenticalVertices
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
					{ vertex.x, vertex.y, vertex.z },
					{ normal.x, normal.y, normal.z },
					{ texCoord.x, texCoord.y }
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

	void Mesh::Load()
	{
		m_VertexBuffer = VertexBuffer::Create(m_Vertices.size() * sizeof(Vertex));
		m_VertexBuffer->SetData(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex));
		m_IndexBuffer = IndexBuffer::Create(m_Indices.data(), m_Indices.size() * sizeof(Index));

		DXR::VertexBufferLayout layout = {
		   { DXR::ShaderDataType::Float3, "a_Position" },
		   { DXR::ShaderDataType::Float3, "a_Normal" },
		   { DXR::ShaderDataType::Float2, "a_TexCoord" },
		};
		m_VertexBuffer->SetLayout(layout);
	}
}