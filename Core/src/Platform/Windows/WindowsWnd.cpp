#include "pch.h"
#include "WindowsWnd.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include <atlbase.h>
#include <atlconv.h>

namespace DXR
{
	Scope<WindowsWnd> Create(const WindowProps& props)
	{
		return CreateScope<WindowsWnd>(props);
	}

	WindowsWnd::WindowsWnd(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWnd::~WindowsWnd()
	{
		Shutdown();
	}

	void WindowsWnd::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		WNDCLASSEX wndClass = { sizeof(wndClass), CS_OWNDC,
			WndProc, 0, 0, GetModuleHandle(nullptr), nullptr,
			LoadCursor(nullptr, IDC_ARROW),
			(HBRUSH)GetStockObject(BLACK_BRUSH),
			nullptr, L"DXR", nullptr };


		if (!RegisterClassEx(&wndClass))
			std::cout << "[RegisterClass]Init Failed" << std::endl;

		HWND wndHandle = CreateWindowEx(0, wndClass.lpszClassName, CA2T(m_Data.Title.c_str()),
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_SIZEBOX | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
			0, 0, m_Data.Width, m_Data.Height, nullptr, nullptr, wndClass.hInstance, nullptr);

		if (wndHandle == nullptr)
			std::cout << "[CerateWindow]Init Failed" << std::endl;

		SetWindowLongPtr(wndHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&m_Data));

		RECT rect = { 0, 0, m_Data.Width, m_Data.Height };
		AdjustWindowRect(&rect, GetWindowLong(wndHandle, GWL_STYLE), false);
		int wx = rect.right - rect.left;
		int wy = rect.bottom - rect.top;
		int sx = (GetSystemMetrics(SM_CXSCREEN) - wx) / 2;
		int sy = (GetSystemMetrics(SM_CYSCREEN) - wy) / 2;
		if (sy < 0) sy = 0;

		SetWindowPos(wndHandle, HWND_TOP, sx, sy, wx, wy,
			(SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
		SetForegroundWindow(wndHandle);

		ShowWindow(wndHandle, SW_NORMAL);

		m_WndClass = &wndClass;
		m_WndHandle = &wndHandle;

		m_Context= RenderingContext::Create(m_WndHandle);
		m_Context->Init();
	}

	void WindowsWnd::OnUpdate()
	{
		DispatchMsg();
		m_Context->SwapBuffer();
	}

	LRESULT WindowsWnd::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_SIZE:
		{
			static bool first = true;  //TODO:The first WM_SIZE call before SetWindowLongPtr can crash the app
			if (first)
			{
				first = false;
				return 0;
			}

			WindowData& data = *reinterpret_cast<WindowData*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			UINT width = LOWORD(lParam);
			UINT height = HIWORD(lParam);
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
			return 0;
		}
		case WM_CLOSE:
		{
			WindowData& data = *reinterpret_cast<WindowData*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			WindowCloseEvent event;
			data.EventCallback(event);
			return 0;
		}
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
		{
			WindowData& data = *reinterpret_cast<WindowData*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			KeyPressedEvent event(static_cast<KeyCode>(wParam), lParam & 0x40000000 ? true : false);
			data.EventCallback(event);
			return 0;
		}
		case WM_SYSKEYUP:
		case WM_KEYUP:
		{
			WindowData& data = *reinterpret_cast<WindowData*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			KeyReleasedEvent event(static_cast<KeyCode>(wParam));
			data.EventCallback(event);
			return 0;
		}
		case WM_CHAR:
		{
			WindowData& data = *reinterpret_cast<WindowData*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			KeyTypedEvent event(static_cast<KeyCode>(wParam));
			data.EventCallback(event);
			return 0;
		}
		case WM_MOUSEMOVE:
		{
			WindowData& data = *reinterpret_cast<WindowData*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			auto point = MAKEPOINTS(lParam);
			MouseMovedEvent event((float)point.x, (float)point.y);
			data.EventCallback(event);
			return 0;
		}
		case WM_MOUSEWHEEL:
		{
			WindowData& data = *reinterpret_cast<WindowData*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			float xOffset = 0, yOffset = 0;
			if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
				yOffset = 1;
			else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
				yOffset = -1;
			MouseScrolledEvent event(xOffset, yOffset);
			data.EventCallback(event);
			return 0;
		}
		case WM_RBUTTONDOWN:
		{
			WindowData& data = *reinterpret_cast<WindowData*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			MouseButtonPressedEvent event(MouseCode::ButtonRight);
			data.EventCallback(event);
			return 0;
		}
		case WM_MBUTTONDOWN:
		{
			WindowData& data = *reinterpret_cast<WindowData*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			MouseButtonPressedEvent event(MouseCode::ButtonMiddle);
			data.EventCallback(event);
			return 0;
		}
		case WM_LBUTTONDOWN:
		{
			WindowData& data = *reinterpret_cast<WindowData*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			MouseButtonPressedEvent event(MouseCode::ButtonLeft);
			data.EventCallback(event);
			return 0;
		}
		case WM_RBUTTONUP:
		{
			WindowData& data = *reinterpret_cast<WindowData*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			MouseButtonReleasedEvent event(MouseCode::ButtonRight);
			data.EventCallback(event);
			return 0;
		}
		case WM_MBUTTONUP:
		{
			WindowData& data = *reinterpret_cast<WindowData*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			MouseButtonReleasedEvent event(MouseCode::ButtonMiddle);
			data.EventCallback(event);
			return 0;
		}
		case WM_LBUTTONUP:
		{
			WindowData& data = *reinterpret_cast<WindowData*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			MouseButtonReleasedEvent event(MouseCode::ButtonLeft);
			data.EventCallback(event);
			return 0;
		}
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	}

	void WindowsWnd::DispatchMsg()
	{
		MSG msg;
		if (!PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE))
			return;
		if (!GetMessage(&msg, nullptr, 0, 0))
			return;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	void WindowsWnd::Shutdown()
	{
		UnregisterClass(m_WndClass->lpszClassName, m_WndClass->hInstance);
		DestroyWindow(*m_WndHandle);
	}
}