#pragma once
#include "Renderer/Camera.h"
#include "Engine/Timestep.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"

#include <utility>
#include <DirectXMath.h>

namespace DXR
{
	class EditorCamera : public Camera
	{
	public:
		EditorCamera() = default;
		EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		inline float GetDistance() const { return m_Distance; }
		inline void SetDistance(float distance) { m_Distance = distance; }

		inline void SetViewportSize(float width, float height) { m_ViewportWidth = width; m_ViewportHeight = height; UpdateProjection(); }

		const DirectX::XMMATRIX& GetViewMatrix() const { return m_ViewMatrix; }
		DirectX::XMMATRIX GetViewProjection() const { return m_ViewMatrix * m_Projection; }

		DirectX::XMVECTOR GetUpDirection() const; //Vec3
		DirectX::XMVECTOR GetRightDirection() const; //Vec3
		DirectX::XMVECTOR GetForwardDirection() const; //Vec3
		const DirectX::XMFLOAT3& GetPosition() const { DirectX::XMFLOAT3 temp; DirectX::XMStoreFloat3(&temp, m_Position); return temp; }
		DirectX::XMVECTOR GetOrientation() const; //Vec3

		float GetPitch() const { return m_Pitch; }
		float GetYaw() const { return m_Yaw; }
	private:
		void UpdateProjection();
		void UpdateView();

		bool OnMouseScroll(MouseScrolledEvent& e);

		void MousePan(const DirectX::XMFLOAT2& delta);
		void MouseRotate(const DirectX::XMFLOAT2& delta);
		void MouseZoom(float delta);

		DirectX::XMVECTOR CalculatePosition() const; //Vec3

		std::pair<float, float> PanSpeed() const;
		float ZoomSpeed() const;
	private:
		float m_FOV = 45.0f, m_AspectRatio = 1.778f, m_NearClip = 0.1f, m_FarClip = 1000.0f;

		DirectX::XMMATRIX m_ViewMatrix;
		DirectX::XMVECTOR m_Position = { 0.0f, 0.0f, 0.0f }; //Vec3
		DirectX::XMVECTOR m_FocalPoint = { 0.0f, 0.0f, 0.0f }; //Vec3

		DirectX::XMVECTOR m_InitialMousePosition = { 0.0f, 0.0f }; //Vec2

		float m_RotationSpeed = 0.8f;
		float m_Distance = 10.0f;
		float m_Pitch = 0.0f, m_Yaw = 0.0f;

		float m_ViewportWidth = 1920.0f, m_ViewportHeight = 1080.0f;
	};
}