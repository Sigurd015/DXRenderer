#pragma once
#include "Events/Event.h"
#include "Renderer/RenderingContext.h"

#include <Windows.h>
#include <string>
#include <functional>

namespace DXR
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
			:EventCallback(callback), Title(title), Width(width), Height(height), VSync(vSync) {}
	};

	class WindowsWnd
	{
	public:
		WindowsWnd(const WindowProps& props);
		virtual ~WindowsWnd();
		void OnUpdate();
		uint32_t GetWidth() const { return m_Data.Width; }
		uint32_t GetHeight() const { return m_Data.Height; }
		void* GetNativeWindow() const { return m_WndHandle; }
		RenderingContext& GetRenderingContext() const { return *m_Context; };
	private:
		static LRESULT WndProc(HWND, UINT, WPARAM, LPARAM);
		void DispatchMsg();
		virtual void Init();
		virtual void Shutdown();
		WNDCLASSEX* m_WndClass;
		HWND* m_WndHandle;
		Scope<RenderingContext> m_Context;
		WindowProps m_Data;
	};

	Scope<WindowsWnd> Create(const WindowProps& props);
}