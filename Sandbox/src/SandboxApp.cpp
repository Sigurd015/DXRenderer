#include "DXR.h"
#include "EntryPoint.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include <iostream>

class ExampleLayer :public DXR::Layer
{
public:
	ExampleLayer() :Layer("ExampleLayer") {}
	~ExampleLayer() {}
	void OnAttach() override {}
	void OnDetach() override {}
	void OnUpdate(DXR::Timestep ts)override
	{
		//std::cout << "Time Step:" << ts << std::endl;
		DXR::RenderCommand::SetClearColor(0.8f, 0.5f, 0.3f, 1.0f);
	}

	void OnEvent(DXR::Event& evnet) override
	{
		DXR::EventDispatcher dispatcher(evnet);
		//dispatcher.Dispatch<DXR::KeyPressedEvent>(DXR_BIND_EVENT_FN(ExampleLayer::OnKeyPressed));
		//dispatcher.Dispatch<DXR::KeyReleasedEvent>(DXR_BIND_EVENT_FN(ExampleLayer::OnKeyReleased));
		//dispatcher.Dispatch<DXR::KeyTypedEvent>(DXR_BIND_EVENT_FN(ExampleLayer::OnKeyTyped));
		//dispatcher.Dispatch<DXR::MouseMovedEvent>(DXR_BIND_EVENT_FN(ExampleLayer::OnMouseMove));
		dispatcher.Dispatch<DXR::MouseButtonPressedEvent>(DXR_BIND_EVENT_FN(ExampleLayer::OnMouseButtonDown));
		dispatcher.Dispatch<DXR::MouseButtonReleasedEvent>(DXR_BIND_EVENT_FN(ExampleLayer::OnMouseButtonUp));
		//dispatcher.Dispatch<DXR::MouseScrolledEvent>(DXR_BIND_EVENT_FN(ExampleLayer::OnMouseScrolled));
	}
	void OnImGuiRender()override {}

	bool OnMouseMove(DXR::MouseMovedEvent& event)
	{
		printf("Mouse Pos: X(%f) Y(%f)\n", event.GetX(), event.GetY());
		return false;
	}

	bool OnMouseButtonDown(DXR::MouseButtonPressedEvent& event)
	{
		std::cout << "MouseButton:" << event.ToString() << "Down" << std::endl;
		return false;
	}

	bool OnMouseButtonUp(DXR::MouseButtonReleasedEvent& event)
	{
		std::cout << "MouseButton:" << event.ToString() << "Up" << std::endl;
		return false;
	}

	bool OnMouseScrolled(DXR::MouseScrolledEvent& event)
	{
		std::cout << "MouseScrolled:" << event.ToString() << std::endl;
		return false;
	}

	bool OnKeyPressed(DXR::KeyPressedEvent& event)
	{
		if (event.IsRepeat())
		{
			printf("Key:%c Repeat\n", (char)(event.GetKeyCode()));
			return false;
		}
		printf("Key:%c Down\n", (char)(event.GetKeyCode()));
		return false;
	}

	bool OnKeyReleased(DXR::KeyReleasedEvent& event)
	{
		printf("Key:%c Up\n", (char)(event.GetKeyCode()));
		return false;
	}

	bool OnKeyTyped(DXR::KeyTypedEvent& event)
	{
		printf("Key:%c Typed\n", (char)(event.GetKeyCode()));
		return false;
	}
};

class Sandbox :public DXR::Application
{
public:
	Sandbox(const DXR::ApplicationSpecification& specification) : DXR::Application(specification)
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

DXR::Application* DXR::CreateApplication(DXR::ApplicationCommandLineArgs args)
{
	DXR::ApplicationSpecification spec;
	spec.Name = "Sandbox";
	spec.WorkingDirectory = "../Sandbox";
	spec.CommandLineArgs = args;

	return new Sandbox(spec);
}