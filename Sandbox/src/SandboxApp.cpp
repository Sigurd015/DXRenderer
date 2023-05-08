#include "DXR.h"
#include "EntryPoint.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include <imgui.h>
#include <iostream>
#include <DirectXMath.h>

struct Vertex
{
	DirectX::XMFLOAT3 Pos;
};

Vertex vertices[] =
{
	{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f)},
	{ DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f)},
	{ DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f) },
	{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f)},
	{ DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f)},
	{ DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f)},
	{ DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f) },
	{ DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f)}
};

uint32_t indices[] =
{
	// 正面
  0, 1, 2,
  2, 3, 0,
  // 左面
  4, 5, 1,
  1, 0, 4,
  // 顶面
  1, 5, 6,
  6, 2, 1,
  // 背面
  7, 6, 5,
  5, 4, 7,
  // 右面
  3, 2, 6,
  6, 7, 3,
  // 底面
  4, 0, 3,
  3, 7, 4
};

struct ConstantBuffer
{
	DirectX::XMMATRIX World;
	DirectX::XMMATRIX View;
	DirectX::XMMATRIX Proj;
	DirectX::XMFLOAT4 Color;
};

class ExampleLayer :public DXR::Layer
{
private:
	DXR::Ref<DXR::VertexArray> m_VertexArray;
	DXR::Ref<DXR::VertexBuffer>	m_VertexBuffer;
	DXR::Ref<DXR::IndexBuffer>	m_IndexBuffer;
	DXR::Ref<DXR::UniformBuffer> m_UniformBuffer;
	DXR::Ref<DXR::Texture2D> m_Texture;
	DXR::Ref<DXR::Shader>	m_Shader;
	ConstantBuffer m_ConstantBuffer = {};
	float Phi, Theta, Scale, Tx, Ty;
	DirectX::XMFLOAT4 color = { 0.3f,0.3f,0.3f,1.0f };
public:
	ExampleLayer() :Layer("ExampleLayer") {}
	~ExampleLayer() {}
	void OnAttach() override
	{
		m_VertexArray = DXR::VertexArray::Create();
		m_VertexBuffer = DXR::VertexBuffer::Create(60 * sizeof(Vertex));
		m_VertexBuffer->SetLayout({
				{ DXR::ShaderDataType::Float3, "Position" },
				/*			{ DXR::ShaderDataType::Float4, "Color"    },*/
							/*{ DXR::ShaderDataType::Float2, "TexCoord" },*/
			});
		m_Shader = DXR::Shader::Create("assets/shaders/TestShader.hlsl");
		m_VertexArray->AddVertexBuffer(m_VertexBuffer, m_Shader);
		m_IndexBuffer = DXR::IndexBuffer::Create(indices, (uint32_t)std::size(indices));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_VertexBuffer->SetData(vertices, sizeof(vertices));
		m_UniformBuffer = DXR::UniformBuffer::Create(sizeof(ConstantBuffer), 0);

		//m_Texture = DXR::Texture2D::Create("assets/textures/Checkerboard.png");
		/*	m_WhiteTexture = DXR::Texture2D::Create(1,1);
			uint32_t whiteTextureData = 0xffffffff;
			m_WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));*/

		m_ConstantBuffer.World = DirectX::XMMatrixIdentity();    // 单位矩阵的转置是它本身
		m_ConstantBuffer.View = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
		));
		m_ConstantBuffer.Proj = DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2, 16.0f / 9.0f, 1.0f, 1000.0f));
		Tx = Ty = Phi = Theta = 0.0f;
		Scale = 1.0f;
		m_ConstantBuffer.Color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	void OnDetach() override
	{}

	void OnUpdate(DXR::Timestep ts)override
	{
		DXR::RenderCommand::SetClearColor(color);
		DXR::RenderCommand::Clear();

		//Phi = DirectX::XMConvertToRadians(Phi);
		//Theta = DirectX::XMConvertToRadians(Theta);
		Phi = DirectX::XMScalarModAngle(Phi);
		Theta = DirectX::XMScalarModAngle(Theta);

		m_ConstantBuffer.World = DirectX::XMMatrixTranspose(
			DirectX::XMMatrixScalingFromVector(DirectX::XMVectorReplicate(Scale)) *
			DirectX::XMMatrixRotationX(Phi) * DirectX::XMMatrixRotationY(Theta) *
			DirectX::XMMatrixTranslation(Tx, Ty, 0.0f));

		m_UniformBuffer->SetData(&m_ConstantBuffer, sizeof(ConstantBuffer));

		//m_Texture->Bind(1);

		DXR::Renderer::Submit(m_Shader, m_VertexArray, DirectX::XMMatrixIdentity());

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
	void OnImGuiRender()override
	{

		if (ImGui::Begin("Use ImGui"))
		{
			if (ImGui::Button("Reset Params"))
			{
				Tx = Ty = Phi = Theta = 0.0f;
				Scale = 1.0f;
			}
			ImGui::SliderFloat("Scale", &Scale, 0.2f, 2.0f);

			ImGui::Text("Phi: %.2f degrees", DirectX::XMConvertToDegrees(Phi));
			ImGui::SliderFloat("##1", &Phi, -DirectX::XM_PI, DirectX::XM_PI, "");
			ImGui::Text("Theta: %.2f degrees", DirectX::XMConvertToDegrees(Theta));
			ImGui::SliderFloat("##2", &Theta, -DirectX::XM_PI, DirectX::XM_PI, "");
			ImGui::ColorEdit4("Color:", &m_ConstantBuffer.Color.x);
		}
		ImGui::End();
	}

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