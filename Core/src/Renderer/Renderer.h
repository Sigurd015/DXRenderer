#pragma once
#include "Camera.h"
#include "Shader.h"
#include "Pipeline.h"
#include "RenderCommandQueue.h"
#include "RenderPass.h"
#include "Mesh.h"

#include <cstdint>
#include <DirectXMath.h>

namespace DXR
{
	class Renderer
	{
	public:
		typedef void(*RenderCommandFn)(void*);

		static void Init();
		static void Shutdown();
		static void SetClearColor(const DirectX::XMFLOAT4& color = { 0.3f,0.3f,0.3f,1.0f });
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginRender(Ref<Pipeline> pipeline);
		static void EndRender();

		template<typename FuncT>
		static void Submit(FuncT&& func)
		{
			auto renderCmd = [](void* ptr)
			{
				auto pFunc = (FuncT*)ptr;
				(*pFunc)();

				// NOTE: Instead of destroying we could try and enforce all items to be trivally destructible
				// however some items like uniforms which contain std::strings still exist for now
				// static_assert(std::is_trivially_destructible_v<FuncT>, "FuncT must be trivially destructible");
				pFunc->~FuncT();
			};
			auto storageBuffer = GetRenderCommandQueue().Allocate(renderCmd, sizeof(func));
			new (storageBuffer) FuncT(std::forward<FuncT>(func));
		}

		static void SubmitStaticMesh(Ref<Mesh>& mesh, Ref<Pipeline>& pipeLine, const DirectX::XMMATRIX& transform = DirectX::XMMatrixIdentity());

		static void WaitAndRender();

	private:
		static RenderCommandQueue& GetRenderCommandQueue();
	};
}
