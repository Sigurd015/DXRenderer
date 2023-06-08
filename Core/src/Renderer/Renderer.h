#pragma once
#include "Renderer/Camera.h"
#include "Renderer/Shader.h"
#include "Renderer/Pipeline.h"

#include <cstdint>
#include <DirectXMath.h>

namespace DXR
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void BeginScene(const Camera& camera, const DirectX::XMMATRIX& transform);
		static void EndScene();
		static void Submit(const Ref<Pipeline>& pipeline, const Ref<Shader>& shader);
	private:
		struct SceneData
		{
			DirectX::XMMATRIX ViewProjectionMatrix;
		};
		static Scope<SceneData> s_SceneData;
	};
}
