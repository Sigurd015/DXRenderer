#include "DXR.h"
#include "EntryPoint.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include <iostream>


struct Vertex
{
	struct
	{
		float x;
		float y;
	} pos;
	struct
	{
		float r;
		float g;
		float b;
		float a;
	} color;
};


uint32_t indices[] =
{
	0,1,2,
	0,2,3,
	0,4,1,
	2,1,5,
};

class ExampleLayer :public DXR::Layer
{
private:
	DXR::Ref<DXR::VertexBuffer>	m_VertexBuffer;
	DXR::Ref<DXR::IndexBuffer>	m_IndexBuffer;
	DXR::Ref<DXR::Shader>	m_Shader;
	DXR::Ref<DXR::VertexArray> m_VertexArray;
public:
	ExampleLayer() :Layer("ExampleLayer") {}
	~ExampleLayer() {}
	void OnAttach() override
	{
		Vertex vertices[] =
		{
			{ 0.0f,0.5f,1.0f,0,0,0 },
			{ 0.5f,-0.5f,0,1.0f,0,0 },
			{ -0.5f,-0.5f,0,0,1.0f,0 },
			{ -0.3f,0.3f,0,1.0f,0,0 },
			{ 0.3f,0.3f,0,0,1.0f,0 },
			{ 0.0f,-0.8f,1.0f,0,0,0 },
		};
		m_VertexArray = DXR::VertexArray::Create();
		m_VertexBuffer = DXR::VertexBuffer::Create(60 * sizeof(Vertex));
		m_VertexBuffer->SetLayout({
			{ DXR::ShaderDataType::Float2, "Position" },
			{ DXR::ShaderDataType::Float4, "Color" },
			});
		m_Shader = DXR::Shader::Create("assets/shaders/TestShader.hlsl");
		m_VertexArray->AddVertexBuffer(m_VertexBuffer, m_Shader);
		m_IndexBuffer = DXR::IndexBuffer::Create(indices, sizeof(indices));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_VertexBuffer->SetData(vertices, sizeof(vertices));
	}

	void OnDetach() override
	{}

	void OnUpdate(DXR::Timestep ts)override
	{
		DXR::RenderCommand::SetClearColor(0, 0, 0, 0);
		DXR::RenderCommand::Clear();
	
		m_Shader->Bind();
		DXR::RenderCommand::DrawIndexed(m_VertexArray, (UINT)std::size(indices));
		//DXR_INFO("Timestep:",ts);
	}

	void OnEvent(DXR::Event& evnet) override
	{
		DXR::EventDispatcher dispatcher(evnet);
		//dispatcher.Dispatch<DXR::KeyPressedEvent>(DXR_BIND_EVENT_FN(ExampleLayer::OnKeyPressed));
		//dispatcher.Dispatch<DXR::KeyReleasedEvent>(DXR_BIND_EVENT_FN(ExampleLayer::OnKeyReleased));
		//dispatcher.Dispatch<DXR::KeyTypedEvent>(DXR_BIND_EVENT_FN(ExampleLayer::OnKeyTyped));
		//dispatcher.Dispatch<DXR::MouseMovedEvent>(DXR_BIND_EVENT_FN(ExampleLayer::OnMouseMove));
		//dispatcher.Dispatch<DXR::MouseButtonPressedEvent>(DXR_BIND_EVENT_FN(ExampleLayer::OnMouseButtonDown));
		//dispatcher.Dispatch<DXR::MouseButtonReleasedEvent>(DXR_BIND_EVENT_FN(ExampleLayer::OnMouseButtonUp));
		//dispatcher.Dispatch<DXR::MouseScrolledEvent>(DXR_BIND_EVENT_FN(ExampleLayer::OnMouseScrolled));
	}
	void OnImGuiRender()override {}

	bool OnMouseMove(DXR::MouseMovedEvent& event)
	{
		DXR_INFO("Mouse Pos:X", event.GetX(), ",Y:", event.GetY());
		return false;
	}

	bool OnMouseButtonDown(DXR::MouseButtonPressedEvent& event)
	{
		DXR_INFO("MouseButton:", event.ToString(), " Down");
		return false;
	}

	bool OnMouseButtonUp(DXR::MouseButtonReleasedEvent& event)
	{
		DXR_INFO("MouseButton:", event.ToString(), " Up");
		return false;
	}

	bool OnMouseScrolled(DXR::MouseScrolledEvent& event)
	{
		DXR_INFO("MouseScrolled:", event.ToString());
		return false;
	}

	bool OnKeyPressed(DXR::KeyPressedEvent& event)
	{
		if (event.IsRepeat())
		{
			DXR_INFO("Key:", (char)(event.GetKeyCode()), " Repeat");
			return false;
		}
		DXR_INFO("Key:", (char)(event.GetKeyCode()), " Down");
		return false;
	}

	bool OnKeyReleased(DXR::KeyReleasedEvent& event)
	{
		DXR_INFO("Key:", (char)(event.GetKeyCode()), " Up");
		return false;
	}

	bool OnKeyTyped(DXR::KeyTypedEvent& event)
	{
		DXR_INFO("Key:", (char)(event.GetKeyCode()), " Typed");
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