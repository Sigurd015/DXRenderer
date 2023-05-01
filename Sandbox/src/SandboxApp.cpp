#include "DXR.h"
#include <Events/KeyEvent.h>

class ExampleLayer :public DXR::Layer
{
public:
	ExampleLayer() :Layer("ExampleLayer") {}
	~ExampleLayer() {}
	void OnAttach() override {}
	void OnDetach() override {}
	void OnUpdate(DXR::Timestep ts)override {}
	void OnEvent(DXR::Event& evnet) override
	{
		DXR::EventDispatcher dispatcher(evnet);
		dispatcher.Dispatch<DXR::KeyPressedEvent>(DXR_BIND_EVENT_FN(ExampleLayer::OnKeyPressed));
		dispatcher.Dispatch<DXR::KeyReleasedEvent>(DXR_BIND_EVENT_FN(ExampleLayer::OnKeyReleased));

	}
	void OnImGuiRender()override {}

	bool OnKeyPressed(DXR::KeyPressedEvent& event)
	{
		printf("%c\n",(char)(event.GetKeyCode()));
		return false;
	}

	bool OnKeyReleased(DXR::KeyReleasedEvent& event)
	{
		printf("%c\n", (char)(event.GetKeyCode()));
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