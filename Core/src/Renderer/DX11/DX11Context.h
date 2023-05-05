#pragma once
#include "Renderer/RenderingContext.h"

#include <d3d11.h>
#include <Windows.h>
#include <wrl.h>

namespace DXR
{
	class DX11Context :public RenderingContext
	{
	public:
		DX11Context(HWND* windowHandle);
		void Init() override;
		void SwapBuffer() override;
		static Microsoft::WRL::ComPtr<ID3D11Device> GetDevice() { return s_Instance->m_Device; }
		static Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetDeviceContext() { return s_Instance->m_DeviceContext; }
		static Microsoft::WRL::ComPtr<IDXGISwapChain> GetSwapChain() { return s_Instance->m_SwapChain; }
	private:
		HWND* m_WindowHandle;
		static DX11Context* s_Instance;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
	};
}