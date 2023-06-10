﻿#include "pch.h"
#include "DX11API.h"
#include "DX11Context.h"
#include "Engine/Application.h"
#include "Platform/DXCommon.h"
#include "Renderer/Renderer.h"

namespace DXR
{
	void DX11RendererAPI::Init()
	{
		m_DeviceContext = DX11Context::GetDeviceContext();
		m_Device = DX11Context::GetDevice();
		m_SwapChain = DX11Context::GetSwapChain();

		SetBuffer(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());
	}

	void DX11RendererAPI::SetClearColor(const DirectX::XMFLOAT4& color)
	{
		m_ClearColor = color;
	}

	void DX11RendererAPI::Clear()
	{
		m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), &m_ClearColor.x);
		m_DeviceContext->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
		m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());
	}

	void DX11RendererAPI::SetBuffer(uint32_t width, uint32_t height, uint32_t x, uint32_t y)
	{
		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
		DX_CHECK_RESULT(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer));
		DX_CHECK_RESULT(m_Device->CreateRenderTargetView(backBuffer.Get(), nullptr, m_RenderTargetView.GetAddressOf()));

		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.Width = width;
		depthStencilDesc.Height = height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		DX_CHECK_RESULT(m_Device->CreateTexture2D(&depthStencilDesc, nullptr, m_DepthStencilBuffer.GetAddressOf()));
		DX_CHECK_RESULT(m_Device->CreateDepthStencilView(m_DepthStencilBuffer.Get(), nullptr, m_DepthStencilView.GetAddressOf()));
		m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());

		D3D11_VIEWPORT viewPort{};
		viewPort.Width = width;
		viewPort.Height = height;
		viewPort.MinDepth = 0;
		viewPort.MaxDepth = 1.0f;
		viewPort.TopLeftX = x;
		viewPort.TopLeftY = y;
		m_DeviceContext->RSSetViewports(1, &viewPort);
	}

	void DX11RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		m_RenderTargetView.Reset();
		m_DepthStencilView.Reset();
		m_DepthStencilBuffer.Reset();

		DX_CHECK_RESULT(m_SwapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0));

		SetBuffer(width, height, x, y);
	}

	void DX11RendererAPI::BeginRender()
	{
		Ref<DX11RendererAPI> instance = CreateRef<DX11RendererAPI>(*this);
		Renderer::Submit([instance]()
			{
				instance->Clear();
			});
	}

	void DX11RendererAPI::BeginRender(Ref<Pipeline>& pipeLine)
	{
		Renderer::Submit([pipeLine]()
			{
				pipeLine->GetSpecification().RenderPass->GetSpecification().TargetFramebuffer->Bind();
			});
	}

	void DX11RendererAPI::EndRender()
	{
		Renderer::WaitAndRender();
		Clear();
	}

	void DX11RendererAPI::SubmitStaticMesh(Ref<Mesh>& mesh, Ref<Pipeline>& pipeLine, const DirectX::XMMATRIX& transform)
	{
		Ref<DX11RendererAPI> instance = CreateRef<DX11RendererAPI>(*this);
		Renderer::Submit([mesh, pipeLine, instance]()
			{
				mesh->GetVertexBuffer()->Bind();
				mesh->GetIndexBuffer()->Bind();
				pipeLine->Bind();	
				mesh->GetMaterial()->Bind();

				//TODO: Set topology based on pipeLine
				//pipeLine->GetSpecification().Topology

				instance->m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				uint32_t count = mesh->GetIndexBuffer()->GetCount();
				instance->m_DeviceContext->DrawIndexed(count, 0, 0);
			});
	}

	//void DX11RendererAPI::DrawLines(const Ref<Pipeline>& pipeline, uint32_t vertexCount)
	//{
	//	pipeline->Bind();
	//	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	//	m_DeviceContext->DrawIndexed(vertexCount, 0, 0);
	//}
}