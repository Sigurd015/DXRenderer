#pragma once
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Layer/Layer.h"
#include "Platform/Windows/WindowsWnd.h"
#include "Layer/LayerStack.h"
#include <chrono>

int main(int argc, char** argv);

namespace DXR
{
	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			return Args[index];
		}
	};

	struct ApplicationSpecification
	{
		std::string Name = "DXR App";
		std::string WorkingDirectory;
		ApplicationCommandLineArgs CommandLineArgs;
	};

	class  Application
	{
	public:
		Application(const ApplicationSpecification& specification);
		virtual ~Application();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void Close();
		WindowsWnd& GetWindow() { return *m_Window; }
		static Application& Get() { return *s_Instance; }
		const ApplicationSpecification& GetSpecification() const { return m_Specification; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		ApplicationSpecification m_Specification;
		Scope<WindowsWnd> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		static Application* s_Instance;
		std::chrono::steady_clock::time_point m_LastFrameTime = std::chrono::steady_clock::now();
		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication(ApplicationCommandLineArgs args);
}