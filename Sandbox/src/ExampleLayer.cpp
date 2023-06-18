#include "ExampleLayer.h"

#include <imgui.h>
#include <iostream>
#include <DirectXMath.h>

ExampleLayer::ExampleLayer() :Layer("ExampleLayer")
{}

void ExampleLayer::OnAttach()
{
	//m_Meshes = DXR::Renderer::GetMesh("Box");
	//m_Meshes = DXR::Renderer::GetMesh("Sphere");
	//m_Meshes = DXR::Renderer::GetMesh("Capsule");
	m_Meshes = DXR::CreateRef<DXR::Mesh>("Box.obj");

	m_CameraDataBuffer = DXR::ConstantBuffer::Create(sizeof(ConstantBuffer), 0);

	m_DiffuseTexture = DXR::Texture2D::Create("assets/textures/Container_Diffuse.png");
	m_SpecularTexture = DXR::Texture2D::Create("assets/textures/Container_Specular.png");

	DXR::FramebufferSpecification fbSpec;
	fbSpec.Attachments = {
		DXR::FramebufferTextureFormat::RGBA8F,
		DXR::FramebufferTextureFormat::Depth };
	fbSpec.Width = 1920;
	fbSpec.Height = 1080;
	fbSpec.ClearColor = { 0.3f, 0.3f, 0.3f, 1.0f };
	m_Framebuffer = DXR::Framebuffer::Create(fbSpec);

	m_Camera = DXR::EditorCamera(30.0f, 1920.0f / 1080.0f, 0.1f, 1000.0f);

	m_RenderPass = DXR::RenderPass::Create({ m_Framebuffer });

	DXR::PipelineSpecification spec;
	spec.Layout = m_Meshes->GetVertexBuffer()->GetLayout();
	spec.RenderPass = m_RenderPass;
	spec.Shader = DXR::Renderer::GetShader("Phong");
	m_Pipeline = DXR::Pipeline::Create(spec);

	m_Material = DXR::Material::Create(spec.Shader);
	m_Material->SetTexture(m_DiffuseTexture, 0); // 0 is Diffuse slot by default
	m_Material->SetTexture(m_SpecularTexture, 1); // 1 is Specular slot by default

	m_Pipeline->SetConstantBuffer(m_CameraDataBuffer);
}

void ExampleLayer::OnDetach()
{}

void ExampleLayer::OnUpdate(DXR::Timestep ts)
{
	// Resize
	if (DXR::FramebufferSpecification spec = m_Framebuffer->GetSpecification();
		m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
		(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
	{
		m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_Camera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
	}
	m_Camera.OnUpdate(ts);

	m_CameraData.ViewProj = DirectX::XMMatrixTranspose(m_Camera.GetViewProjection());

	DXR::Renderer::BeginRenderPass(m_RenderPass);

	m_CameraData.Model = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixScalingFromVector(DirectX::XMVectorReplicate(1.0f)) *
		DirectX::XMMatrixRotationX(0.25f) * DirectX::XMMatrixRotationY(0.5f) *
		DirectX::XMMatrixTranslation(-0.5f, -0.5f, -0.5f));
	m_CameraDataBuffer->SetData(&m_CameraData, sizeof(ConstantBuffer));
	DXR::Renderer::SubmitStaticMesh(m_Meshes, m_Material, m_Pipeline);

	DXR::Renderer::EndRenderPass(m_RenderPass);
}

void ExampleLayer::OnEvent(DXR::Event& evnet)
{
	m_Camera.OnEvent(evnet);
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
void ExampleLayer::OnImGuiRender()
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

	UI_Tool();

	ImGui::Begin("Viewport");
	DXR::Application::Get().GetImGuiLayer()->BlockEvents(!ImGui::IsWindowHovered());
	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
	ImGui::Image(m_Framebuffer->GetColorAttachment(), ImVec2{ m_ViewportSize.x, m_ViewportSize.y });
	ImGui::End();

	ImGui::End();
}

void ExampleLayer::UI_Tool()
{
	if (ImGui::Begin("Tools"))
	{

	}
	ImGui::End();
}

bool ExampleLayer::OnMouseMove(DXR::MouseMovedEvent& event)
{
	DXR_INFO("Mouse Pos:X", event.GetX(), ",Y:", event.GetY());
	return false;
}

bool ExampleLayer::OnMouseButtonDown(DXR::MouseButtonPressedEvent& event)
{
	DXR_INFO("MouseButton:", event.ToString(), " Down");
	return false;
}

bool ExampleLayer::OnMouseButtonUp(DXR::MouseButtonReleasedEvent& event)
{
	DXR_INFO("MouseButton:", event.ToString(), " Up");
	return false;
}

bool ExampleLayer::OnMouseScrolled(DXR::MouseScrolledEvent& event)
{
	DXR_INFO("MouseScrolled:", event.ToString());
	return false;
}

bool ExampleLayer::OnKeyPressed(DXR::KeyPressedEvent& event)
{
	if (event.IsRepeat())
	{
		DXR_INFO("Key:", (char)(event.GetKeyCode()), " Repeat");
		return false;
	}
	DXR_INFO("Key:", (char)(event.GetKeyCode()), " Down");
	return false;
}

bool ExampleLayer::OnKeyReleased(DXR::KeyReleasedEvent& event)
{
	DXR_INFO("Key:", (char)(event.GetKeyCode()), " Up");
	return false;
}

bool ExampleLayer::OnKeyTyped(DXR::KeyTypedEvent& event)
{
	DXR_INFO("Key:", (char)(event.GetKeyCode()), " Typed");
	return false;
}