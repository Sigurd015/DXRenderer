#include "pch.h"
#include "WindowsWnd.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include <atlbase.h>
#include <atlconv.h>
#include <backends/imgui_impl_win32.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace DXR
{
	Scope<WindowsWnd> Create(const WindowProps& props)
	{
		return CreateScope<WindowsWnd>(props);
	}

	WindowsWnd::WindowsWnd(const WindowProps& props) :m_Data(props)
	{
		Init();
	}

	WindowsWnd::~WindowsWnd()
	{
		Shutdown();
	}

	void WindowsWnd::Init()
	{
		WNDCLASSEX wndClass = { sizeof(wndClass), CS_OWNDC,
			WndProc, 0, 0, GetModuleHandle(nullptr), nullptr,
			nullptr, nullptr, nullptr, L"DXR", nullptr };

		if (!RegisterClassEx(&wndClass))
			DXR_INFO("[RegisterWndClass]Failed");

		RECT rect = { 0, 0, m_Data.Width, m_Data.Height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		HWND wndHandle = CreateWindow(wndClass.lpszClassName, CA2T(m_Data.Title.c_str()),
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, wndClass.hInstance, this);

		if (wndHandle == nullptr)
			DXR_INFO("[CerateWindow]Failed");

		ShowWindow(wndHandle, SW_SHOW);

		m_WndClass = &wndClass;
		m_WndHandle = &wndHandle;

		m_Context = RenderingContext::Create(m_WndHandle);
	}

	void WindowsWnd::OnUpdate()
	{
		DispatchMsg();
		m_Context->SwapBuffer(m_Data.VSync);
	}

	LRESULT WindowsWnd::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;

		switch (msg)
		{
		case WM_CREATE:
		{
			const CREATESTRUCTW* const temp = reinterpret_cast<CREATESTRUCTW*>(lParam);
			WindowsWnd* const windowsWnd = static_cast<WindowsWnd*>(temp->lpCreateParams);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&windowsWnd->m_Data));
			break;
		}
		case WM_SIZE:
		{
			static bool first = true;  //TODO:The first WM_SIZE call before RenderingContext::Create() can crash the app
			if (first)
			{
				first = false;
				break;
			}

			const bool minimized = wParam == SIZE_MINIMIZED;
			const bool maximized = wParam == SIZE_MAXIMIZED;
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			if(minimized)
			{
				WindowResizeEvent event(0, 0);
				data.EventCallback(event);
				break;
			}
			if (maximized)
			{
				RECT rect = {};
				rect.right = ::GetSystemMetrics(SM_CXSCREEN);
				rect.bottom = ::GetSystemMetrics(SM_CYSCREEN);
				WindowResizeEvent event(rect.right, rect.bottom);
				data.EventCallback(event);
				break;
			}

			RECT rect = {};
			GetClientRect(hWnd, &rect);
			ClientToScreen(hWnd, (LPPOINT)&rect.left);
			ClientToScreen(hWnd, (LPPOINT)&rect.right);
			WindowResizeEvent event(rect.right - rect.left, rect.bottom - rect.top);
			data.EventCallback(event);
			break;
		}
		case WM_CLOSE:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			WindowCloseEvent event;
			data.EventCallback(event);
			break;
		}
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			KeyPressedEvent event(wParam, lParam & 0x40000000 ? true : false);
			data.EventCallback(event);
			break;
		}
		case WM_SYSKEYUP:
		case WM_KEYUP:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			KeyReleasedEvent event(wParam);
			data.EventCallback(event);
			break;
		}
		case WM_CHAR:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			KeyTypedEvent event(wParam);
			data.EventCallback(event);
			break;
		}
		case WM_MOUSEMOVE:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			auto point = MAKEPOINTS(lParam);
			MouseMovedEvent event((float)point.x, (float)point.y);
			data.EventCallback(event);
			break;
		}
		case WM_MOUSEWHEEL:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			float xOffset = 0, yOffset = 0;
			if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
				yOffset = 1;
			else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
				yOffset = -1;
			MouseScrolledEvent event(xOffset, yOffset);
			data.EventCallback(event);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			MouseButtonPressedEvent event(Mouse::ButtonRight);
			data.EventCallback(event);
			break;
		}
		case WM_MBUTTONDOWN:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			MouseButtonPressedEvent event(Mouse::ButtonMiddle);
			data.EventCallback(event);
			break;
		}
		case WM_LBUTTONDOWN:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			MouseButtonPressedEvent event(Mouse::ButtonLeft);
			data.EventCallback(event);
			break;
		}
		case WM_RBUTTONUP:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			MouseButtonReleasedEvent event(Mouse::ButtonRight);
			data.EventCallback(event);
			break;
		}
		case WM_MBUTTONUP:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			MouseButtonReleasedEvent event(Mouse::ButtonMiddle);
			data.EventCallback(event);
			break;
		}
		case WM_LBUTTONUP:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			MouseButtonReleasedEvent event(Mouse::ButtonLeft);
			data.EventCallback(event);
			break;
		}
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	}

	void WindowsWnd::DispatchMsg()
	{
		MSG msg;
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void WindowsWnd::Shutdown()
	{
		UnregisterClass(m_WndClass->lpszClassName, m_WndClass->hInstance);
		DestroyWindow(*m_WndHandle);
	}
}