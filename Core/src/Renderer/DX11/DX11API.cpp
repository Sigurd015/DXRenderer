#include "pch.h"
#include "Renderer/DX11/DX11API.h"
#include "Renderer/DX11/DX11Context.h"
#include "Application.h"

namespace DXR
{
	void DX11RendererAPI::Init()
	{
		m_DeviceContext = DX11Context::GetDeviceContext();
		m_Device = DX11Context::GetDevice();
		m_SwapChain = DX11Context::GetSwapChain();

		Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;
		m_SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &backBuffer);
		DXR_ASSERT(m_Device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_RenderTargetView));

		D3D11_DEPTH_STENCIL_DESC depthStencil = {};
		depthStencil.DepthEnable = true;
		depthStencil.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencil.DepthFunc = D3D11_COMPARISON_LESS;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState;
		DXR_ASSERT(m_Device->CreateDepthStencilState(&depthStencil, &depthStencilState));
		m_DeviceContext->OMSetDepthStencilState(depthStencilState.Get(), 1);

		D3D11_TEXTURE2D_DESC depthTexture = {};
		depthTexture.Width = Application::Get().GetWindow().GetWidth();
		depthTexture.Height = Application::Get().GetWindow().GetHeight();
		depthTexture.MipLevels = 1;
		depthTexture.ArraySize = 1;
		depthTexture.Format = DXGI_FORMAT_D32_FLOAT;
		depthTexture.SampleDesc.Count = 1;
		depthTexture.SampleDesc.Quality = 0;
		depthTexture.Usage = D3D11_USAGE_DEFAULT;
		depthTexture.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilTexture;
		DXR_ASSERT(m_Device->CreateTexture2D(&depthTexture, nullptr, &depthStencilTexture));

		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilView = {};
		depthStencilView.Format = DXGI_FORMAT_D32_FLOAT;
		depthStencilView.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilView.Texture2D.MipSlice = 0;
		DXR_ASSERT(m_Device->CreateDepthStencilView(depthStencilTexture.Get(), &depthStencilView, &m_DepthStencilView));
		m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());
	}

	void DX11RendererAPI::SetClearColor(const DirectX::XMFLOAT4& color)
	{
		m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), &color.x);
	}

	void DX11RendererAPI::Clear()
	{
		m_DeviceContext->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1, 0);
	}

	void DX11RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		D3D11_VIEWPORT viewPort{};
		viewPort.Width = (float)width;
		viewPort.Height = (float)height;
		viewPort.MinDepth = 0;
		viewPort.MaxDepth = 1.0f;
		viewPort.TopLeftX = (float)x;
		viewPort.TopLeftY = (float)y;
		m_DeviceContext->RSSetViewports(1, &viewPort);
	}

	void DX11RendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		m_DeviceContext->DrawIndexed(count, 0, 0);
	}
	void DX11RendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
	{}
	void DX11RendererAPI::SetLineWidth(float width)
	{}
}