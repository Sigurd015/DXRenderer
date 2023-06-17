#pragma once
#include "DXR.h"

struct ConstantBuffer
{
	DirectX::XMMATRIX World;
	DirectX::XMMATRIX ViewProj;
	DirectX::XMFLOAT4 Color;
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
	float Phi, Theta, Scale, Tx, Ty;

	DXR::Ref<DXR::ConstantBuffer> m_ConstantBuffer;
	DXR::Ref<DXR::Texture2D> m_Texture;
	DXR::Ref<DXR::Framebuffer> m_Framebuffer;
	ConstantBuffer m_ConstantBufferData = {};

	DXR::Ref<DXR::Mesh> m_Meshes;
	DXR::Ref<DXR::RenderPass> m_RenderPass;
	DXR::Ref<DXR::Pipeline> m_Pipeline;
	DXR::Ref<DXR::Material> m_Material;
};