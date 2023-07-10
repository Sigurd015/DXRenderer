#pragma once
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Layer/Layer.h"
#include "Platform/Windows/WindowsWnd.h"
#include "Layer/LayerStack.h"
#include "Layer/ImGui/ImGuiLayer.h""

#include <chrono>

int main(int argc, char** argv);

namespace DXC
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
		bool EnableImGui = true;
	};

	class  Application
	{
	public:
		Application(const ApplicationSpecification& specification);
		virtual ~Application();
		void Run();
		void RenderImGui();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void Close();
		WindowsWnd& GetWindow() { return *m_Window; }
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
		static Application& Get() { return *s_Instance; }
		const ApplicationSpecification& GetSpecification() const { return m_Specification; }
	private:

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		ApplicationSpecification m_Specification;
		Scope<WindowsWnd> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		static Application* s_Instance;
		std::chrono::steady_clock::time_point m_LastFrameTime = std::chrono::steady_clock::now();
	};

	Application* CreateApplication(ApplicationCommandLineArgs args);
}