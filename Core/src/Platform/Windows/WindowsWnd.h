#pragma once
#include "Events/Event.h"
#include "Renderer/RendererContext.h"
#include "Renderer/RendererAPI.h"

#include <Windows.h>
#include <string>
#include <functional>

namespace DXC
{
	using EventCallBackFn = std::function<void(Event&)>;

	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		bool VSync;
		EventCallBackFn EventCallback;

		WindowProps(const EventCallBackFn& callback, const std::string& title = "DXR",
			uint32_t width = 1920, uint32_t height = 1080, bool vSync = true)
			:EventCallback(callback), Title(title), Width(width), Height(height), VSync(vSync)
		{}
	};

	class WindowsWnd
	{
	public:
		WindowsWnd(const WindowProps& props);
		~WindowsWnd();
		void OnUpdate();
		uint32_t GetWidth() const { return m_Data.Width; }
		uint32_t GetHeight() const { return m_Data.Height; }
		void WindowsWnd::SetWindowTitle(const std::string& title);
		void* GetNativeWindow() const { return m_WndHandle; }
		RendererContext& GetRenderingContext() const { return *m_Context; };
	private:
		static LRESULT WndProc(HWND, UINT, WPARAM, LPARAM);
		void DispatchMsg();
		void Init();
		void Shutdown();
		HWND m_WndHandle;
		Scope<RendererContext> m_Context;
		WindowProps m_Data;
	};

	Scope<WindowsWnd> Create(const WindowProps& props);
}