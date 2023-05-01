#include "pch.h"
#include "WindowsWnd.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include <atlbase.h>
#include <atlconv.h>

namespace DXR
{
	Scope<WindowsWnd> WindowsWnd::Create(const WindowProps& props)
	{
		return CreateScope<WindowsWnd>(props);
	}

	HWND WindowsWnd::m_WndHandle = nullptr;
	HDC WindowsWnd::m_WndDc = nullptr;

	WindowsWnd::WindowsWnd(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWnd::~WindowsWnd()
	{
		Shutdown();
	}

	void WindowsWnd::OnUpdate()
	{
		DispatchMsg();
	}

	void WindowsWnd::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		WNDCLASSEX wc = { sizeof(wc), CS_OWNDC,
			WndProc, 0, 0, GetModuleHandle(nullptr), nullptr,
			LoadCursor(nullptr, IDC_ARROW),
			(HBRUSH)GetStockObject(BLACK_BRUSH),
			nullptr, L"RendererScreen", nullptr };

		if (!RegisterClassEx(&wc))
			std::cout << "[RegisterClass]Init Failed" << std::endl;

		m_WndHandle = CreateWindowEx(0, L"RendererScreen", CA2T(m_Data.Title.c_str()),
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
			200, 200, 1920, 1080, nullptr, nullptr, wc.hInstance, nullptr);

		if (m_WndHandle == nullptr)
			std::cout << "[CerateWindow]Init Failed" << std::endl;

		SetWindowLongPtr(m_WndHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&m_Data));

		ShowWindow(m_WndHandle, SW_NORMAL);

	}

	LRESULT WindowsWnd::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_CLOSE:
		{
			WindowData& data = *reinterpret_cast<WindowData*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			WindowCloseEvent event;
			data.EventCallback(event);
			break;
		}
		break;
		case WM_KEYDOWN:
		{
			WindowData& data = *reinterpret_cast<WindowData*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			KeyPressedEvent event(static_cast<KeyCode>(wParam), 0);
			data.EventCallback(event);
			break;
		}
		case WM_KEYUP:
		{
			WindowData& data = *reinterpret_cast<WindowData*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			KeyReleasedEvent event(static_cast<KeyCode>(wParam));
			data.EventCallback(event);
			break;
		}
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	}

	void WindowsWnd::DispatchMsg()
	{
		BOOL bRet;
		MSG msg;
		while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
		{
			if (bRet == -1)
			{
				// handle the error and possibly exit
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				break;
			}
		}
	}

	void WindowsWnd::Shutdown()
	{

	}
}