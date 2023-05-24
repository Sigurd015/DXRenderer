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
	int Id;
};

Vertex vertices[] =
{
	{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f),5},
	{ DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f),5},
	{ DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f),5 },
	{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f),5},
	{ DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f),5},
	{ DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f),5},
	{ DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f),5 },
	{ DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f),5}
};

uint32_t indices[] =
{
  0, 1, 2,
  2, 3, 0,
  4, 5, 1,
  1, 0, 4,
  1, 5, 6,
  6, 2, 1,
  7, 6, 5,
  5, 4, 7,
  3, 2, 6,
  6, 7, 3,
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
	DirectX::XMFLOAT2 m_ViewportSize = { 0.0f, 0.0f };
	DirectX::XMFLOAT2 m_ViewportBounds[2];
	DXR::Ref<DXR::VertexArray> m_VertexArray;
	DXR::Ref<DXR::VertexBuffer>	m_VertexBuffer;
	DXR::Ref<DXR::IndexBuffer>	m_IndexBuffer;
	DXR::Ref<DXR::UniformBuffer> m_UniformBuffer;
	DXR::Ref<DXR::Texture2D> m_Texture;
	DXR::Ref<DXR::Shader>	m_Shader;
	DXR::Ref<DXR::Framebuffer> m_Framebuffer;
	ConstantBuffer m_ConstantBuffer = {};
	float Phi, Theta, Scale, Tx, Ty;
public:
	ExampleLayer() :Layer("ExampleLayer") {}
	~ExampleLayer() {}
	void OnAttach() override
	{
		m_VertexArray = DXR::VertexArray::Create();
		m_VertexBuffer = DXR::VertexBuffer::Create(60 * sizeof(Vertex));
		m_VertexBuffer->SetLayout({
				{ DXR::ShaderDataType::Float3, "Position" },
				{ DXR::ShaderDataType::Int, "Id" },
				/*			{ DXR::ShaderDataType::Float4, "Color"    },*/
							/*{ DXR::ShaderDataType::Float2, "TexCoord" },*/
			});
		m_Shader = DXR::Shader::Create("TestShader");
		m_VertexArray->AddVertexBuffer(m_VertexBuffer, m_Shader);
		m_IndexBuffer = DXR::IndexBuffer::Create(indices, (uint32_t)std::size(indices));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_VertexBuffer->SetData(vertices, sizeof(vertices));
		m_UniformBuffer = DXR::UniformBuffer::Create(sizeof(ConstantBuffer), 0);

		m_Texture = DXR::Texture2D::Create("assets/textures/Checkerboard.png");
		/*	m_WhiteTexture = DXR::Texture2D::Create(1,1);
			uint32_t whiteTextureData = 0xffffffff;
			m_WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));*/

		m_ConstantBuffer.World = DirectX::XMMatrixIdentity();
		m_ConstantBuffer.View = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
		));
		Tx = Ty = Phi = Theta = 0.0f;
		Scale = 1.0f;
		m_ConstantBuffer.Color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		DXR::FramebufferSpecification fbSpec;
		fbSpec.Attachments = { DXR::FramebufferTextureFormat::RGBA8, DXR::FramebufferTextureFormat::RED_INTEGER ,DXR::FramebufferTextureFormat::Depth };
		fbSpec.Width = 1920;
		fbSpec.Height = 1080;
		m_Framebuffer = DXR::Framebuffer::Create(fbSpec);
	}

	void OnDetach() override
	{}

	void OnUpdate(DXR::Timestep ts)override
	{
		// Resize
		if (DXR::FramebufferSpecification spec = m_Framebuffer->GetSpecification();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_ConstantBuffer.Proj = DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2, m_ViewportSize.x / m_ViewportSize.y, 1.0f, 1000.0f));
		}

		m_Framebuffer->Bind();
		DXR::RenderCommand::SetClearColor({ 0.3f,0.3f,0.3f,1.0f });
		DXR::RenderCommand::Clear();
		m_Framebuffer->ClearAttachment(1, -1);

		m_ConstantBuffer.World = DirectX::XMMatrixTranspose(
			DirectX::XMMatrixScalingFromVector(DirectX::XMVectorReplicate(Scale)) *
			DirectX::XMMatrixRotationX(Phi) * DirectX::XMMatrixRotationY(Theta) *
			DirectX::XMMatrixTranslation(Tx, Ty, 0.0f));

		m_UniformBuffer->SetData(&m_ConstantBuffer, sizeof(ConstantBuffer));

		//m_Texture->Bind(1);

		DXR::Renderer::Submit(m_Shader, m_VertexArray, DirectX::XMMatrixIdentity());

		m_Framebuffer->Unbind();

		//DXR_INFO("Timestep:",ts);

		ImVec2 mousePos = ImGui::GetMousePos();
		mousePos.x -= m_ViewportBounds[0].x;
		mousePos.y -= m_ViewportBounds[0].y;
		DirectX::XMFLOAT2 viewportSize;
		DirectX::XMStoreFloat2(&viewportSize, DirectX::XMVectorSubtract(DirectX::XMLoadFloat2(&m_ViewportBounds[1]), DirectX::XMLoadFloat2(&m_ViewportBounds[0])));
		
		int mouseX = (int)mousePos.x;
		int mouseY = (int)mousePos.y;

		if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
		{
			int pixelData = m_Framebuffer->ReadPixel(1, mouseX, mouseY);
			//Pick Object
		}
	}

	void OnEvent(DXR::Event& evnet) override
	{
		DXR::EventDispatcher dispatcher(evnet);
		if (DXR::Input::IsKeyPressed(DXR::Key::A))
		{
			DXR_INFO("A Is pressed!");
		}
		if (DXR::Input::IsKeyPressed(DXR::Key::G))
		{
			DXR_INFO("G Is pressed!");
		}
		if (DXR::Input::IsKeyPressed(DXR::Key::U))
		{
			DXR_INFO("U Is pressed!");
		}
		//auto [x, y] = DXR::Input::GetMousePosition();
		//DXR_INFO("Mouse X(", x, "), Y(", y, ")");

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
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		style.WindowMinSize.x = minWinSizeX;

		if (ImGui::Begin("Tools"))
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

		ImGui::Begin("Viewport");
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
		ImGui::Image(m_Framebuffer->GetColorAttachment(), ImVec2{ m_ViewportSize.x, m_ViewportSize.y });

		auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();
		m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
		m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };
		ImGui::End();

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