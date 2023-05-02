#pragma once
#include "Renderer/RenderingContext.h"

#include <d3d11.h>
#include <Windows.h>

namespace DXR
{
	class DX11Context :public RenderingContext
	{
	public:
		DX11Context(HWND* windowHandle);
		~DX11Context();
		void Init() override;
		void SwapBuffer() override;
		static void SetClearColor(float r, float g, float b, float a);
	private:
		HWND* m_WindowHandle;
		IDXGISwapChain* m_SwapChain;
		ID3D11Device* m_Device;
		static ID3D11DeviceContext* m_DeviceContext;
		static ID3D11RenderTargetView* m_RenderTargetView;
	};
}