#pragma once
#include "Events/Event.h"

#include <Windows.h>
#include <string>
#include <functional>

namespace DXR
{
	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "DXR", uint32_t width = 1920, uint32_t height = 1080) :Title(title), Width(width), Height(height) {}
	};

	class WindowsWnd
	{
	public:
		using EventCallBackFn = std::function<void(Event&)>;

		static Scope<WindowsWnd> Create(const WindowProps& props);

		WindowsWnd(const WindowProps& props);
		virtual ~WindowsWnd();
		void OnUpdate();
		unsigned int GetWidth() const  { return m_Data.Width; }
		unsigned int GetHeight() const  { return m_Data.Height; }
		void SetEventCallback(const EventCallBackFn& callback)  { m_Data.EventCallback = callback; }
	private:
		static LRESULT WndProc(HWND, UINT, WPARAM, LPARAM);
		void DispatchMsg();
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
		static HWND m_WndHandle;
		static HDC m_WndDc;
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;

			EventCallBackFn EventCallback;
		};
		WindowData m_Data;
	};
}