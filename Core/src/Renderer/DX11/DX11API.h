#pragma once
#include "Renderer/RendererAPI.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"

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
		void Clear() override;
		void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
		void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) override;
		void SetLineWidth(float width) override;
		void DX11RendererAPI::SetAttachments(bool renderToBackbuffer = false);
		void ReSetAttachments();
		static const DirectX::XMFLOAT4& GetClearColor() { return s_Instance->m_ClearColor; }
		static DX11RendererAPI* Get() { return s_Instance; }
	private:
		void SetBuffer(uint32_t width, uint32_t height, uint32_t x = 0, uint32_t y = 0);
		static DX11RendererAPI* s_Instance;
		bool m_RenderToBackbuffer = true;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_DepthStencilBuffer;
		DirectX::XMFLOAT4 m_ClearColor;
	};
}