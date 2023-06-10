#pragma once
#include "Renderer/Mesh.h"

namespace DXR
{
	class MeshFactory
	{
	public:
		static Ref<Mesh> CreateBox(const DirectX::XMFLOAT3& size);
		static Ref<Mesh> CreateSphere(float radius);
		static Ref<Mesh> CreateCapsule(float radius, float height);
	};

}