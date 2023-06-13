#pragma once
#include "Renderer/RendererAPI.h"
#include "Renderer/Pipeline.h"
#include "Renderer/Shader.h"
#include "Renderer/Material.h"
#include "Renderer/RenderPass.h"

#include <d3d11.h>
#include <Windows.h>
#include <wrl.h>
#include <DirectXMath.h>

namespace DXR
{
	class DX11RendererAPI : public RendererAPI
	{
	public:
		void Init() override;
		void SetClearColor(const DirectX::XMFLOAT4& color) override;
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		void BeginRender() override;
		void EndRender() override;
		void BeginPipeline(const Ref<RenderPass>& renderPass) override;
		void EndPipeline(const Ref<RenderPass>& renderPass) override;

		void SubmitStaticMesh(const Ref<Mesh>& mesh, const Ref<Pipeline>& pipeline) override;
	private:
		void ResetToBackBuffer();
		void SetBuffer(uint32_t width, uint32_t height, uint32_t x = 0, uint32_t y = 0);
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_DepthStencilBuffer;
		DirectX::XMFLOAT4 m_ClearColor = { 0.3f,0.3f,0.3f,1.0f };
	};
}