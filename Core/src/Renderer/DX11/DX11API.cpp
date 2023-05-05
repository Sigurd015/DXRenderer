#include "pch.h"
#include "Renderer/DX11/DX11API.h"
#include "Renderer/DX11/DX11Context.h"
#include "Application.h"

namespace DXR
{
	//---------------TODO:TEMP-------------
	struct Vertex
	{
		struct
		{
			float x;
			float y;
		} pos;
		struct
		{
			float r;
			float g;
			float b;
			float a;
		} color;
	};

	uint32_t indices[] =
	{
		0,1,2,
		0,2,3,
		0,4,1,
		2,1,5,
	};
	//---------------TODO:TEMP-------------
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

	void DX11RendererAPI::SetClearColor(float r, float g, float b, float a)
	{
		const float color[] = { r,g,b,a };
		m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), color);
	}

	void DX11RendererAPI::Clear()
	{
		m_DeviceContext->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1, 0);
	}

	void DX11RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		D3D11_VIEWPORT viewPort{};
		viewPort.Width = width;
		viewPort.Height = height;
		viewPort.MinDepth = 0;
		viewPort.MaxDepth = 1;
		viewPort.TopLeftX = x;
		viewPort.TopLeftY = y;
		m_DeviceContext->RSSetViewports(1, &viewPort);
	}

	void DX11RendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		m_DeviceContext->DrawIndexed(count, 0, 0);
		DXR_INFO("Draw:(IndexCount:", count, ")");
		////---------------------------------------------------------TODO:TEMP------------------------------
		//Vertex vertices[] =
		//{
		//	{ 0.0f,0.5f,1.0f,0,0,0 },
		//	{ 0.5f,-0.5f,0,1.0f,0,0 },
		//	{ -0.5f,-0.5f,0,0,1.0f,0 },
		//	{ -0.3f,0.3f,0,1.0f,0,0 },
		//	{ 0.3f,0.3f,0,0,1.0f,0 },
		//	{ 0.0f,-0.8f,1.0f,0,0,0 },
		//};
		//Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
		//D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
		//vertexBufferDesc.ByteWidth = 10*sizeof(vertices);
		//vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		//vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		//vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		//vertexBufferDesc.MiscFlags = 0;
		//vertexBufferDesc.StructureByteStride = 0;

		//DXR_INFO("VertexBufferCreate:(ByteWidth:", 10 * sizeof(vertices), ")");

		//DXR_ASSERT(m_Device->CreateBuffer(&vertexBufferDesc, nullptr, &pVertexBuffer));

		//// Bind vertex buffer to pipeline
		//const uint32_t stride = sizeof(Vertex);
		//const uint32_t offset = 0u;

		//m_DeviceContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);

		//DXR_INFO("VertexBufferBind:(Stride:", stride, ")");

		//D3D11_MAPPED_SUBRESOURCE mappedResource;
		//ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

		//m_DeviceContext->Map(pVertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		////  Update the vertex buffer here.
		//memcpy(mappedResource.pData, vertices, sizeof(vertices));
		////  Reenable GPU access to the vertex buffer data.
		//m_DeviceContext->Unmap(pVertexBuffer.Get(), 0);
		//
		//DXR_INFO("VertexBufferSetData:(DataSize:", sizeof(vertices), ")");


		//m_Shader = DXR::Shader::Create("assets/shaders/TestShader.hlsl");

		//// create index buffer
		//Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
		//D3D11_BUFFER_DESC ibd = {};
		//ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		//ibd.Usage = D3D11_USAGE_DEFAULT;
		//ibd.CPUAccessFlags = 0u;
		//ibd.MiscFlags = 0u;
		//ibd.ByteWidth = sizeof(indices);
		//ibd.StructureByteStride = 0;
		//D3D11_SUBRESOURCE_DATA isd = {};
		//isd.pSysMem = indices;
		//DXR_ASSERT(m_Device->CreateBuffer(&ibd, &isd, &pIndexBuffer));

		//DXR_INFO("IndexBufferCreate:(ByteWidth:", sizeof(indices), ")");

		//// bind index buffer
		//m_DeviceContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
		//
		////Set primitive topology to triangle list(groups of 3 vertices)
		//m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//m_Shader->Bind();

		//m_DeviceContext->DrawIndexed((UINT)std::size(indices), 0u, 0u);
		//DXR_INFO("Draw:(IndexCount:", (UINT)std::size(indices), ")");
		////---------------------------------------------------------TODO:TEMP------------------------------
	}
	void DX11RendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
	{}
	void DX11RendererAPI::SetLineWidth(float width)
	{}
}