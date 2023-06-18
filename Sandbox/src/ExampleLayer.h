#pragma once
#include "DXR.h"

struct ConstantBuffer
{
	DirectX::XMMATRIX Model;
	DirectX::XMMATRIX ViewProj;
};

struct DirectionalLight
{
	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT3 Direction;
	float padding;
};

class ExampleLayer :public DXR::Layer
{
public:
	ExampleLayer();
	~ExampleLayer() = default;
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(DXR::Timestep ts) override;
	void OnEvent(DXR::Event& evnet) override;
	void OnImGuiRender() override;
private:
	void UI_Tool();
	bool OnMouseMove(DXR::MouseMovedEvent& event);
	bool OnMouseButtonDown(DXR::MouseButtonPressedEvent& event);
	bool OnMouseButtonUp(DXR::MouseButtonReleasedEvent& event);
	bool OnMouseScrolled(DXR::MouseScrolledEvent& event);
	bool OnKeyPressed(DXR::KeyPressedEvent& event);
	bool OnKeyReleased(DXR::KeyReleasedEvent& event);
	bool OnKeyTyped(DXR::KeyTypedEvent& event);

	DirectX::XMFLOAT2 m_ViewportSize = { 0.0f, 0.0f };
	DirectX::XMFLOAT2 m_ViewportBounds[2];
	DXR::EditorCamera m_Camera;

	DXR::Ref<DXR::Framebuffer> m_Framebuffer;

	ConstantBuffer m_CameraData = {};
	ConstantBuffer m_DirLightData = {};
	DXR::Ref<DXR::ConstantBuffer> m_CameraDataBuffer;
	DXR::Ref<DXR::ConstantBuffer> m_DirLightDataBuffer;

	DXR::Ref<DXR::Texture2D> m_DiffuseTexture;
	DXR::Ref<DXR::Texture2D> m_SpecularTexture;

	DXR::Ref<DXR::Mesh> m_Meshes;
	DXR::Ref<DXR::RenderPass> m_RenderPass;
	DXR::Ref<DXR::Pipeline> m_Pipeline;
	DXR::Ref<DXR::Material> m_Material;
};