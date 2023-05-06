#include "pch.h"
#include "Renderer/DX11/DX11Context.h"
#include "Application.h"

namespace DXR
{
	DX11Context* DX11Context::s_Instance = nullptr;

	DX11Context::DX11Context(HWND* windowHandle) :m_WindowHandle(windowHandle)
	{
		Init();
	}

	void DX11Context::Init()
	{
		s_Instance = this;

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

		DXR_ASSERT(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &dscd,
			&m_SwapChain, &m_Device, nullptr, &m_DeviceContext));
	}

	void DX11Context::SwapBuffer(bool VSync)
	{
		m_SwapChain->Present(VSync, 0);
	}
}