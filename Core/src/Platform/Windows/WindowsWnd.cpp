#include "pch.h"
#include "WindowsWnd.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include <atlbase.h>
#include <atlconv.h>
#include <backends/imgui_impl_win32.h>

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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

	void WindowsWnd::SetWindowTitle(const std::string& title)
	{
		SetWindowTextA(m_WndHandle, (m_Data.Title + title).c_str());
	}

	void WindowsWnd::Init()
	{
		WNDCLASSEX wndClass = { sizeof(wndClass), CS_OWNDC,
			WndProc, 0, 0, GetModuleHandle(nullptr), nullptr,
			nullptr, nullptr, nullptr, L"DXR", nullptr };

		DXR_ASSERT(RegisterClassEx(&wndClass));

		RECT rect = { 0, 0, m_Data.Width, m_Data.Height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		m_WndHandle = CreateWindowEx(0, wndClass.lpszClassName, CA2T(m_Data.Title.c_str()),
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, wndClass.hInstance, this);

		DXR_ASSERT(m_WndHandle);

		ShowWindow(m_WndHandle, SW_SHOW);

		m_Context = RenderingContext::Create(&m_WndHandle);
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
			return 0;
		}
		case WM_SIZE:
		{
			static bool first = true;  //TODO:The first WM_SIZE call before RenderingContext::Create() can crash the app
			if (first)
			{
				first = false;
				return 0;
			}

			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			if (wParam == SIZE_MINIMIZED)
			{
				data.Width = data.Height = 0;
			}
			else
			{
				data.Width = LOWORD(lParam);
				data.Height = HIWORD(lParam);
			}

			WindowResizeEvent event(data.Width, data.Height);
			data.EventCallback(event);
			return 0;
		}
		case WM_CLOSE:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			WindowCloseEvent event;
			data.EventCallback(event);
			return 0;
		}
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			KeyPressedEvent event(wParam, lParam & 0x40000000 ? true : false);
			data.EventCallback(event);
			return 0;
		}
		case WM_SYSKEYUP:
		case WM_KEYUP:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			KeyReleasedEvent event(wParam);
			data.EventCallback(event);
			return 0;
		}
		case WM_CHAR:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			KeyTypedEvent event(wParam);
			data.EventCallback(event);
			return 0;
		}
		case WM_MOUSEMOVE:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			auto point = MAKEPOINTS(lParam);
			MouseMovedEvent event((float)point.x, (float)point.y);
			data.EventCallback(event);
			return 0;
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
			return 0;
		}
		case WM_RBUTTONDOWN:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			MouseButtonPressedEvent event(Mouse::ButtonRight);
			data.EventCallback(event);
			return 0;
		}
		case WM_MBUTTONDOWN:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			MouseButtonPressedEvent event(Mouse::ButtonMiddle);
			data.EventCallback(event);
			return 0;
		}
		case WM_LBUTTONDOWN:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			MouseButtonPressedEvent event(Mouse::ButtonLeft);
			data.EventCallback(event);
			return 0;
		}
		case WM_RBUTTONUP:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			MouseButtonReleasedEvent event(Mouse::ButtonRight);
			data.EventCallback(event);
			return 0;
		}
		case WM_MBUTTONUP:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			MouseButtonReleasedEvent event(Mouse::ButtonMiddle);
			data.EventCallback(event);
			return 0;
		}
		case WM_LBUTTONUP:
		{
			WindowProps& data = *reinterpret_cast<WindowProps*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			MouseButtonReleasedEvent event(Mouse::ButtonLeft);
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
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void WindowsWnd::Shutdown()
	{
		DestroyWindow(m_WndHandle);
	}
}