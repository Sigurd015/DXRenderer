#include "pch.h"
#include "Renderer/DX11/DX11Context.h"

namespace DXR
{
	ID3D11DeviceContext* DX11Context::m_DeviceContext = nullptr;
	ID3D11RenderTargetView* DX11Context::m_RenderTargetView = nullptr;

	DX11Context::DX11Context(HWND* windowHandle) :m_WindowHandle(windowHandle)
	{}

	DX11Context::~DX11Context()
	{
		if (m_RenderTargetView != nullptr)
			m_RenderTargetView->Release();
		if (m_DeviceContext != nullptr)
			m_DeviceContext->Release();
		if (m_SwapChain != nullptr)
			m_SwapChain->Release();
		if (m_Device != nullptr)
			m_Device->Release();
	}

	void DX11Context::Init()
	{
		DXGI_SWAP_CHAIN_DESC dscd = {};
		dscd.BufferDesc.Width = 0;
		dscd.BufferDesc.Height = 0;
		dscd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		dscd.BufferDesc.RefreshRate.Denominator = 0;
		dscd.BufferDesc.RefreshRate.Numerator = 0;
		dscd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		dscd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		dscd.SampleDesc.Count = 1;
		dscd.SampleDesc.Quality = 0;
		dscd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		dscd.BufferCount = 1;
		dscd.OutputWindow = *m_WindowHandle;
		dscd.Windowed = true;
		dscd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		dscd.Flags = 0;

		D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &dscd,
			&m_SwapChain, &m_Device, nullptr, &m_DeviceContext);

		ID3D11Resource* backBuffer;
		m_SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&backBuffer));
		m_Device->CreateRenderTargetView(backBuffer, nullptr, &m_RenderTargetView);
		backBuffer->Release();
	}

	void DX11Context::SwapBuffer()
	{
		m_SwapChain->Present(1u, 0u);
	}

	void DX11Context::SetClearColor(float r, float g, float b, float a)
	{
		const float color[] = { r,g,b,a };
		m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, color);
	}
}